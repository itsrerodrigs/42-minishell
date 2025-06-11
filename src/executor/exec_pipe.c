/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 09:42:48 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "sig.h"
#include "builtins.h"

extern volatile sig_atomic_t g_child_running;

/*
 * @brief Sets up input/output redirections for the child process.
 * @param cmd Pointer to the current command.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param is_pipe Flag indicating if the current command is piped.
 */
static void setup_redirections(t_command *cmd, int prev_pipe_read_fd, int pipefd[2],
        int is_pipe)
{
    if (prev_pipe_read_fd != -1)
    {
        if (dup2(prev_pipe_read_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 error for previous pipe input");
            exit(1);
        }
        close(prev_pipe_read_fd);
    }
    if (is_pipe)
    {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) == -1)
        {
            perror("dup2 error for current pipe output");
            exit(1);
        }
        close(pipefd[1]);
    }
    if (apply_redirections(cmd) != 0)
        exit(1);
}

static void exec_pipe_child(t_shell *shell, t_command *cmd,
    int prev_pipe_read_fd, int pipefd[2], int is_pipe)
{    
    char            *cmd_path;
    builtin_func    func;

    set_child_signals();
    //setpgid(0, 0);
    setup_redirections(cmd, prev_pipe_read_fd, pipefd, is_pipe);

    func = find_builtin(cmd->args[0]);
    if (func)
    {
        shell->exit_status = func(shell, cmd->args);
        exit(shell->exit_status);
    }
    else
    {
        cmd_path = find_executable(cmd->cmd, shell);
        if (!cmd_path)
        {
            ft_putstr_fd(cmd->cmd, STDERR_FILENO);
            ft_putendl_fd(": command not found", STDERR_FILENO);
            exit(127);
        }
        execve(cmd_path, cmd->args, shell->envp);
        perror("minishell: execve failed");
        free(cmd_path); 
        exit(EXIT_FAILURE);
    }
}

// static void close_parent_pipe_fds(int pipefd[2], int *prev_fd, int is_pipe)
// {
//     if (*prev_fd != -1)
//     {
//         close(*prev_fd);
//         *prev_fd = -1;
//     }        
//     if (is_pipe)
//     {
//         close(pipefd[0]);
//         *prev_fd = pipefd[0];
//     }
//     else
//         *prev_fd = -1;
// }

static void handle_parent_pipe_fds(int pipefd[2], int *prev_pipe_read_fd_ptr, int is_pipe)
{
    if (*prev_pipe_read_fd_ptr != -1)
    {
        close(*prev_pipe_read_fd_ptr);
        *prev_pipe_read_fd_ptr = -1; // Mark as closed
    }
    if (is_pipe)
    {
        close(pipefd[1]);
        *prev_pipe_read_fd_ptr = pipefd[0];
    }
    else
        *prev_pipe_read_fd_ptr = -1;
}
static void handle_parent_process_in_loop(t_shell *shell, pid_t pid, int pipefd[2],
                                          int *prev_pipe_read_fd_ptr, int is_pipe, int *last_executed_pid_ptr)
{
    if (shell->shell_is_interactive)
        set_foreground_process(shell->shell_terminal_fd, pid); // Set foreground to the child's PGID

    handle_parent_pipe_fds(pipefd, prev_pipe_read_fd_ptr, is_pipe);
    *last_executed_pid_ptr = pid;
}

// static void exec_pipe_loop(t_shell *shell, t_command *first_cmd,
//                                          int pipe_fds[2], int *pid_tracker_ptr, int *last_executed_pid_ptr)
// {
//     t_command   *current_cmd;
//     int         prev_pipe_read_fd;

//     current_cmd = first_cmd;
//     prev_pipe_read_fd = -1;

//     while (current_cmd)
//     {
//         *pid_tracker_ptr = fork_and_pipe(pipe_fds, pid_tracker_ptr, current_cmd->is_pipe);
//         if (*pid_tracker_ptr < 0)
//         {
//             perror("minishell: fork or pipe failed");
//             shell->exit_status = 1;
//             break;
//         }
//         if (*pid_tracker_ptr == 0)
//         {
//             set_child_signals();
//             exec_pipe_child(shell, current_cmd, pid_tracker_ptr, pipe_fds, current_cmd->is_pipe);
//         }
//         else
//         {
//             if (shell->shell_is_interactive)
//                 set_foreground_process(shell->shell_terminal_fd, *pid_tracker_ptr);

//             close_parent_pipe_fds(pipe_fds, pid_tracker_ptr, current_cmd->is_pipe);
//             *last_executed_pid_ptr = *pid_tracker_ptr;
//         }
//         current_cmd = current_cmd->next;
//     }
// }
static void exec_pipe_loop(t_shell *shell, t_command *first_cmd,
                                         int *last_executed_pid_ptr) 
{
    t_command   *current_cmd;
    int         pipe_fds[2]; 
    int         prev_pipe_read_fd;
    pid_t       pid;

    current_cmd = first_cmd;
    prev_pipe_read_fd = -1;

    while (current_cmd)
    {
        if (is_builtin_parent_executable(current_cmd))
        {
            int saved_stdin = dup(STDIN_FILENO);
            int saved_stdout = dup(STDOUT_FILENO);
            int exit_code = 1;
            if (saved_stdin == -1 || saved_stdout == -1)
            {
                perror("dup failed for builtin redirection");
                shell->exit_status = 1;
                if (current_cmd->heredoc_pipe_read_fd != 1)
                {
                    close(current_cmd->heredoc_pipe_read_fd);
                    current_cmd->heredoc_pipe_read_fd = -1;
                }
                break;
            }
            if (apply_redirections(current_cmd) == 0)
            {
                builtin_func func = find_builtin(current_cmd->args[0]);
                if (func)
                {
                    exit_code = func(shell, current_cmd->args);
                }
            } 
            else
            {
                exit_code = 1;
            }
            shell->exit_status = exit_code;

            if (dup2(saved_stdin, STDERR_FILENO) == -1)
            {
                perror("dup2 restore stdin failed");
                exit(1);
            }
            close(saved_stdin);
            if (dup2(saved_stdout, STDOUT_FILENO) == -1)
            {
                perror("dup2 restore stdout failed");
                exit(1);
            }
            close(saved_stdout);
            if (current_cmd->heredoc_pipe_read_fd != -1)
            {
                close(current_cmd->heredoc_pipe_read_fd);
                current_cmd->heredoc_pipe_read_fd = -1;
            }
            current_cmd = current_cmd->next;
            continue;
        }
        pipe_fds[0] = -1;
        pipe_fds[1] = -1;
        if (current_cmd->is_pipe)
        {
            if (pipe(pipe_fds) == -1)
            {
                perror("minishell: pipe failed");
                shell->exit_status = 1;
                if (prev_pipe_read_fd != -1)
                    close(prev_pipe_read_fd);
                if (current_cmd->heredoc_pipe_read_fd != 1)
                    close(current_cmd->heredoc_pipe_read_fd);
                break;
            }
        }
        pid = fork();
        if (pid < 0)
        {
            perror("minishell: fork failed");
            shell->exit_status = 1;
            if (pipe_fds[0] != -1) { close(pipe_fds[0]); close(pipe_fds[1]); }
            if (prev_pipe_read_fd != -1) close(prev_pipe_read_fd);
            break;
        }
        if (pid == 0) 
            exec_pipe_child(shell, current_cmd, prev_pipe_read_fd, pipe_fds, current_cmd->is_pipe);
        else 
            handle_parent_process_in_loop(shell, pid, pipe_fds, &prev_pipe_read_fd,
                                          current_cmd->is_pipe, last_executed_pid_ptr);
        current_cmd = current_cmd->next;
    }
    if (prev_pipe_read_fd != -1)
        close(prev_pipe_read_fd);
}


static void pipe_cleanup(t_shell *shell, int last_executed_pid, t_old_signals *old_sa)
{
    if (shell->shell_is_interactive)
        set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);

    pipe_wait_children(shell, last_executed_pid);
    restore_signals(&old_sa->int_sa, &old_sa->quit_sa);
    g_child_running = 0;
}

void exec_pipeline(t_shell *shell, t_command *first_cmd)
{
    t_command       *current_cmd_start;
    t_old_signals   old_sa;
    int             last_executed_pid;

    current_cmd_start = first_cmd;
    last_executed_pid = -1;

    save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);
    exec_pipe_loop(shell, current_cmd_start, &last_executed_pid);
    pipe_cleanup(shell, last_executed_pid, &old_sa);
}
