/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/02 18:02:38 by mmariano         ###   ########.fr       */
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

/*
 * @brief Executes the command: handles redirections,
	builtins and external commands.
 * @param shell Pointer to shell context.
 * @param cmd Pointer to the current command.
 */
static void	exec_command(t_shell *shell, t_command *cmd)
{
	char	*cmd_path;

	if (exec_builtin(shell))
		exit(shell->exit_status);
	cmd_path = find_executable(cmd->cmd, shell);
	if (!cmd_path)
	{
		ft_putendl_fd("command not found", STDERR_FILENO);
		exit(127);
	}
	execve(cmd_path, cmd->args, shell->envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

/*
 * @brief Executes a sequence of piped commands.

	* @param shell Pointer to shell context containing environment and command list.
 * @param first_cmd Pointer to the first command in the pipeline.
 */
/* void exec_pipeline(t_shell *shell, t_command *first_cmd)
{
	int			pipefd[2];
	int			prev_fd;
	t_command	*current;
	pid_t		pid;

	prev_fd = -1;
	current = first_cmd;
	while (current)
	{
		pid = fork_and_pipe(pipefd, &prev_fd, current->is_pipe);
		if (pid == 0) // Child process
		{
			setup_redirections(current, &prev_fd, pipefd, current->is_pipe);
			exec_command(shell, current);
		}
		else if (pid > 0) // Parent process
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (current->is_pipe)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
			else
				prev_fd = -1;
		}
		else
			return ; // fork or pipe error
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
}
 */

static void	pipeline_child_process(t_shell *shell, t_command *cmd, int *prev_fd,
		int pipefd[2], int is_pipe)
{
	(void)is_pipe;
	set_child_default_signals();
	setup_redirections(cmd, prev_fd, pipefd, cmd->is_pipe);
	exec_command(shell, cmd);
}

static void	pipeline_parent_fd_management(int *prev_fd, int pipefd[2], int is_pipe)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (is_pipe)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
	else
		*prev_fd = -1;
}

static void	wait_for_pipeline_children(t_shell *shell, pid_t last_pid)
{
	pid_t	waited_pid;
	int		status;

	while (1)
	{
		waited_pid = wait(&status);
		if (waited_pid < 0)
			break ;
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGINT)
				ft_putendl_fd("Interrupted by signal", STDERR_FILENO);
		}
	}
}

void exec_pipeline(t_shell *shell, t_command *first_cmd)
{

    int             pipe_fds[2]; // 1. For pipe file descriptors
    int             pid_tracker; // 2. Used for current PID (0 for child, >0 for parent), also acts as prev_fd.
    t_command       *current_cmd; // 3. Iterator for command list
    t_old_signals   old_parent_signals; // 4. Stores old signal handlers
    int             last_executed_pid; // 5. Tracks the PID of the last command for exit status

    pid_tracker = -1;
    current_cmd = first_cmd;
    last_executed_pid = -1;

    g_child_running = 1;
    save_and_ignore_signals(&old_parent_signals.int_sa, &old_parent_signals.quit_sa);
    while (current_cmd)
    {
        pid_tracker = fork_and_pipe(pipe_fds, &pid_tracker, current_cmd->is_pipe);
        if (pid_tracker == 0) // Child process
            pipeline_child_process(shell, current_cmd, &pid_tracker, pipe_fds, current_cmd->is_pipe);
        else if (pid_tracker > 0) // Parent process
        {
            pipeline_parent_fd_management(pipe_fds, &pid_tracker, current_cmd->is_pipe);
            last_executed_pid = pid_tracker; // Store the PID of the last command
        }
        else // Fork or pipe error
        {
            perror("command failed due to fork/pipe error");
            shell->exit_status = 1; // Set a generic error status
            break; // Exit loop on critical error
        }
        current_cmd = current_cmd->next;
    }
    wait_for_pipeline_children(shell, last_executed_pid);
    restore_signals(&old_parent_signals.int_sa, &old_parent_signals.quit_sa); 
    g_child_running = 0;
}
