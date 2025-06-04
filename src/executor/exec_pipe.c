/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 03:26:26 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "sig.h"

/*
* @brief executes a command whithin a pipeline's child process
*/

static void exec_pipe_child(t_shell *shell, t_command *cmd,
    t_pipe_data *pdata)
{
    set_child_signals();
    setup_child_redirs(cmd, pdata);
    exec_command(shell, cmd);
    exit(shell->exit_status);
}

/*
* @brief main loop to process the pipeline
*/
static void process_pipe_loop(t_shell *shell, t_command *first_cmd, 
                                int *last_executed_pid_ptr)
{
    t_command *current_cmd;
    t_pipe_data pdata;
    pid_t   child_pid;

    pdata.prev_fd = -1;
    current_cmd = first_cmd;
    while (current_cmd)
    {
        pdata.output_pipe = (current_cmd->next !=NULL);
        child_pid = pipe_n_fork(&pdata);
        if (child_pid < 0)
        {
            handle_pipe_err(shell, &pdata);
            break;
        }
        else if (child_pid == 0)
            exec_pipe_child(shell, current_cmd, &pdata);
        else
            handle_pipe_parent(shell, &pdata, child_pid, last_executed_pid_ptr);
        current_cmd = current_cmd->next;
    }
    close_fd(pdata.prev_fd);
}

/*
* @brief waits for all child processes in a pipeline
*/
void wait_pipeline_children(t_shell *shell, int last_executed_pid)
{
    int status;
    pid_t wpid;

    while ((wpid = waitpid(-1, &status, 0)) > 0)
    {
        if (wpid == last_executed_pid)
        {
            if (WIFEXITED(status))
                shell->exit_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->exit_status = 128 + WTERMSIG(status);
        }
    }
}


/*
* @brief main function to execute a pipeline of commands
*/
void exec_pipeline(t_shell *shell, t_command *first_cmd)
{
    t_old_signals old_sa;
    int last_executed_pid;

    last_executed_pid = -1;
    g_child_running = 1;
    save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);
    process_pipe_loop(shell, first_cmd, &last_executed_pid);
    if (shell->shell_is_interactive)
        set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);
    wait_pipeline_children(shell, last_executed_pid);
    restore_signals(&old_sa.int_sa, &old_sa.quit_sa);
    g_child_running = 0;
}

/*
 * @brief Creates a pipe if needed and forks a new process.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param is_pipe Flag indicating if the current command is piped.
 * @return PID of the forked process, or -1 on error.

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


 * @brief Sets up input/output redirections for the child process.
 * @param cmd Pointer to the current command.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param is_pipe Flag indicating if the current command is piped.
 
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
*/



/*
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
*/
