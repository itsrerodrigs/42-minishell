/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 14:39:44 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/*
 * @brief Creates a pipe if needed and forks a new process.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param is_pipe Flag indicating if the current command is piped.
 * @return PID of the forked process, or -1 on error.
 */
static pid_t fork_and_pipe(int pipefd[2], int *prev_fd, int is_pipe)
{
	(void)prev_fd;

	if (is_pipe)
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return -1;
		}

	pid_t pid = fork();
	if (pid < 0)
		perror("fork");

	return pid;
}

/*
 * @brief Sets up input/output redirections for the child process.
 * @param cmd Pointer to the current command.
 * @param prev_fd Pointer to previous read end of pipe.
 * @param pipefd Array of two integers for pipe file descriptors.
 * @param is_pipe Flag indicating if the current command is piped.
 */
static void setup_redirections(t_command *cmd, int *prev_fd, int pipefd[2], int is_pipe)
{
	(void)cmd;

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
 * @brief Executes the command: handles redirections, builtins and external commands.
 * @param shell Pointer to shell context.
 * @param cmd Pointer to the current command.
 */
static void exec_command(t_shell *shell, t_command *cmd)
{
	char *cmd_path;

	if (apply_redirections(cmd))
		exit(1);
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
void exec_pipeline(t_shell *shell, t_command *first_cmd)
{
	int pipefd[2];
	int prev_fd = -1;
	t_command *current = first_cmd;

	while (current)
	{
		pid_t pid = fork_and_pipe(pipefd, &prev_fd, current->is_pipe);
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
			return; // fork or pipe error

		current = current->next;
	}

	while (wait(NULL) > 0)
		;
}