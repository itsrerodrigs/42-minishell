/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/03 13:12:49 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "sig.h"

/*
 * @brief Creates a pipe if needed and forks a new process.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param is_pipe Flag indicating if the current command is piped.
 * @return PID of the forked process, or -1 on error.
 */
static pid_t	fork_and_pipe(int pipefd[2], int *prev_fd, int is_pipe)
{
	pid_t	pid;

	(void)prev_fd;
	if (is_pipe)
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	pid = fork();
	if (pid < 0)
		perror("fork");
	return (pid);
}

/*
 * @brief Sets up input/output redirections for the child process.
 * @param cmd Pointer to the current command.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param is_pipe Flag indicating if the current command is piped.
 */
static void	setup_redirections(t_command *cmd, int *prev_fd, int pipefd[2],
		int is_pipe)
{
	if (apply_redirections(cmd) != 0)
		exit(1);
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	if (is_pipe)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

static void exec_pipe_child(t_shell *shell, t_command *cmd,
    int *prev_fd, int pipefd[2], int is_pipe)
{
    (void)is_pipe;
    set_child_signals();
    setup_redirections(cmd, prev_fd, pipefd, is_pipe);
    exec_command(shell, cmd);
}

static void pipe_fd_parent(int pipefd[2], int *prev_fd, int is_pipe)
{
    if (*prev_fd != -1)
        close(*prev_fd);
    if (is_pipe)
    {
        close(pipefd[0]);
        *prev_fd = pipefd[0];
    }
    else
        *prev_fd = -1;
}

static void exec_pipe_loop(t_shell *shell, t_command *first_cmd,
                                         int pipe_fds[2], int *pid_tracker_ptr, int *last_executed_pid_ptr)
{
    t_command *current_cmd;

    current_cmd = first_cmd;

    while (current_cmd)
    {
        *pid_tracker_ptr = fork_and_pipe(pipe_fds, pid_tracker_ptr, current_cmd->is_pipe);
        if (*pid_tracker_ptr < 0)
        {
            perror("minishell: fork or pipe failed");
            shell->exit_status = 1;
            break;
        }
        if (*pid_tracker_ptr == 0)
        {
            set_child_signals();
            exec_pipe_child(shell, current_cmd, pid_tracker_ptr, pipe_fds, current_cmd->is_pipe);
        }
        else
        {
            if (shell->shell_is_interactive)
                set_foreground_process(shell->shell_terminal_fd, *pid_tracker_ptr);

            pipe_fd_parent(pipe_fds, pid_tracker_ptr, current_cmd->is_pipe);
            *last_executed_pid_ptr = *pid_tracker_ptr;
        }
        current_cmd = current_cmd->next;
    }
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
    int pipe_fds[2];
    int pid_tracker;
    t_command *current_cmd_start;
    t_old_signals old_sa;
    int last_executed_pid;

    pid_tracker = -1;
    current_cmd_start = first_cmd;
    last_executed_pid = -1;

    g_child_running = 1;
    save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);
    exec_pipe_loop(shell, current_cmd_start, pipe_fds, &pid_tracker, &last_executed_pid);
    pipe_cleanup(shell, last_executed_pid, &old_sa);
}
