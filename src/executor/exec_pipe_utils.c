/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 01:11:22 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 04:46:57 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "sig.h"
#include <stdio.h>
#include <errno.h> // Para a variável global errno e strerror

/*
* @brief closes a file descriptor if it's valid (not -1).
* @param fd the file destriptor to close
*/
void close_fd(int fd)
{
    if (fd != -1)
        close(fd);
}

/*
* @brief handle fork and pipe errors in the parent process
*/
void handle_pipe_err(t_shell *shell, t_pipe_data *pdata)
{
    shell->exit_status = 1;
    close_fd(pdata->prev_fd);
    if (pdata->output_pipe)
    {
        close_fd(pdata->pipe_fd[0]);
        close_fd(pdata->pipe_fd[1]);
    }
}

/*
* @brief creates a pipe and or forks a new process
*/
pid_t    pipe_n_fork(t_pipe_data *pdata)
{
    char debug_msg[512];
    pid_t pid;

    snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Entered. Output pipe needed: %d. PID: %d\n", pdata->output_pipe, getpid());
    write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    if (pdata->output_pipe)
    {
        snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Attempting to create pipe. PID: %d\n", getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
        if(pipe(pdata->pipe_fd) == -1)
        {
            snprintf(debug_msg, sizeof(debug_msg), "ERROR pipe_n_fork: pipe() failed! Errno: %d (%s). PID: %d\n", errno, strerror(errno), getpid());
            write(STDERR_FILENO, debug_msg, strlen(debug_msg));
            perror("minishell: pipe failed");
            return (-1);
        }
        snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Pipe created: read_end=%d, write_end=%d. PID: %d\n", pdata->pipe_fd[0], pdata->pipe_fd[1], getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    }
    else
    {
        pdata->pipe_fd[0] = -1;
        pdata->pipe_fd[1] = -1;
        snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: No output pipe needed (last command). pipe_fd set to [-1, -1]. PID: %d\n", getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    }
    snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Attempting to fork. PID: %d\n", getpid());
    write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    pid = fork();
    if (pid < 0)
    {
        snprintf(debug_msg, sizeof(debug_msg), "ERROR pipe_n_fork: fork() failed! Errno: %d (%s). PID: %d\n", errno, strerror(errno), getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
        perror("minishell: fork failed");
    }
    else if (pid == 0)
    {
        snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Child process created. PID: %d\n", getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    }
    else
    {
        snprintf(debug_msg, sizeof(debug_msg), "pipe_n_fork: Parent process. Child PID: %d. Parent PID: %d\n", pid, getpid());
        write(STDERR_FILENO, debug_msg, strlen(debug_msg));
    }
    return (pid);
}

/*
* @brief set up input/output redirections for the child process
*/

void setup_child_redirs(t_command *cmd, t_pipe_data *pdata)
{
    (void)cmd;
    char debug_msg[512]; 
    //if (apply_redirections(cmd) != 0)
       // exit(1);
    snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: === setup_child_redirs ===\n", getpid());
    snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Initial STDIN_FILENO = %d, STDOUT_FILENO = %d\n", getpid(), STDIN_FILENO, STDOUT_FILENO);
    snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: pdata->prev_fd = %d, pdata->output_pipe = %d\n", getpid(), pdata->prev_fd, pdata->output_pipe);
    if (pdata->prev_fd != -1)
    {
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Redirecting STDIN from %d to %d\n", getpid(), pdata->prev_fd, STDIN_FILENO);
        dup2(pdata->prev_fd, STDIN_FILENO);
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: STDIN_FILENO after dup2 (input pipe) = %d\n", getpid(), STDIN_FILENO);
    }
    if (pdata->output_pipe)
    {
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Redirecting STDOUT from %d to %d\n", getpid(), pdata->pipe_fd[1], STDOUT_FILENO);
        dup2(pdata->pipe_fd[1], STDOUT_FILENO);
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: STDOUT_FILENO after dup2 (output pipe) = %d\n", getpid(), STDOUT_FILENO);
    }
    snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Closing original pipe FDs...\n", getpid());
    if (pdata->prev_fd != -1)
    {
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Closing pdata->prev_fd (%d)\n", getpid(), pdata->prev_fd);
        close_fd(pdata->prev_fd);
    }
    if (pdata->output_pipe)
    {
        snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: Closing pdata->pipe_fd[0] (%d) and pdata->pipe_fd[1] (%d)\n", getpid(), pdata->pipe_fd[0], pdata->pipe_fd[1]);
        close_fd(pdata->pipe_fd[0]);
        close_fd(pdata->pipe_fd[1]);
    }
    snprintf(debug_msg, sizeof(debug_msg), "CHILD %d: === setup_child_redirs END ===\n", getpid());
}

/*
* @brief handles logic in the parent process during pipeline execution
*/
void handle_pipe_parent(t_shell *shell, t_pipe_data *pdata, 
    pid_t child_pid, int *last_executed_pid_ptr)
{
    (void)shell;
    char debug_msg[512]; 
    snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: === handle_pipe_parent for child %d ===\n", getpid(), child_pid);
    snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: Initial pdata->prev_fd = %d\n", getpid(), pdata->prev_fd);
    snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: pdata->output_pipe = %d\n", getpid(), pdata->output_pipe);

    //if (shell->shell_is_interactive)
        //set_foreground_process(shell->shell_terminal_fd, child_pid);
    snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: Closing pdata->prev_fd (%d)\n", getpid(), pdata->prev_fd);
    close_fd(pdata->prev_fd);
    if (pdata->output_pipe)
    {
        snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: Output pipe exists. Closing pdata->pipe_fd[1] (%d)\n", getpid(), pdata->pipe_fd[1]);
        close_fd(pdata->pipe_fd[1]);
        pdata->prev_fd = pdata->pipe_fd[0];
        snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: Updated pdata->prev_fd for next cmd to %d (from pdata->pipe_fd[0])\n", getpid(), pdata->prev_fd);
    }
    else // Este é o ÚLTIMO comando do pipeline, não há pipe de saída
    {
        // Certifique-se de que não estamos tentando fechar FDs inválidos aqui
        snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: Last command. No output pipe. pdata->prev_fd remains %d (will be closed outside loop)\n", getpid(), pdata->prev_fd);
    }
    *last_executed_pid_ptr = child_pid;
    snprintf(debug_msg, sizeof(debug_msg), "PARENT %d: === handle_pipe_parent END ===\n", getpid());
}
