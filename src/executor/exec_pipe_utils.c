/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:58:47 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 15:15:55 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets up I/O for a child process within a pipeline.
 */
void	setup_child_redirections(t_command *cmd, int p_fd, int p[2], int is_p)
{
	if (p_fd != -1)
	{
		if (dup2(p_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 error for previous pipe input");
			exit(1);
		}
		close(p_fd);
	}
	if (is_p)
	{
		close(p[0]);
		if (dup2(p[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error for current pipe output");
			exit(1);
		}
		close(p[1]);
	}
	if (apply_redirections(cmd) != 0)
		exit(1);
	(void)is_p;
}

/**
 * @brief The logic executed by a forked child process in a pipeline.
 */
void	exec_pipe_child(t_shell *shell, t_command *cmd, int p_fd, int p[2])
{
	char			*cmd_path;
	builtin_func	func;

	set_child_signals();
	setup_child_redirections(cmd, p_fd, p, cmd->is_pipe);
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

/**
 * @brief Manages pipe file descriptors in the parent process after a fork.
 */
void	handle_parent_fds(int pipefd[2], int *prev_fd_ptr, int is_pipe)
{
	if (*prev_fd_ptr != -1)
	{
		close(*prev_fd_ptr);
		*prev_fd_ptr = -1;
	}
	if (is_pipe)
	{
		close(pipefd[1]);
		*prev_fd_ptr = pipefd[0];
	}
	else
		*prev_fd_ptr = -1;
}

/**
 * @brief Waits for all child processes in a pipeline to complete.
 */
void	wait_for_children(t_shell *shell, pid_t last_pid)
{
	pid_t	waited_pid;
	int		status;

	if (last_pid != -1)
	{
		waited_pid = waitpid(last_pid, &status, 0);
		if (waited_pid == last_pid)
			update_exit_status_from_wait_status(shell, status);
	}
	while (waitpid(-1, &status, WNOHANG) > 0)
	{
	}
}
