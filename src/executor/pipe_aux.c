/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:18:03 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 21:54:15 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Saves STDIN and STDOUT file descriptors.
 * @param saved_stdin Pointer to store original STDIN FD.
 * @param saved_stdout Pointer to store original STDOUT FD.
 */
void	s_save_fds_for_builtin(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
}

/**
 * @brief Restores STDIN and STDOUT and closes saved FDs.
 * @param saved_stdin Original STDIN FD.
 * @param saved_stdout Original STDOUT FD.
 */
void	s_restore_and_close_fds(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("dup2 restore stdin failed");
	}
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2 restore stdout failed");
	}
	close(saved_stdin);
	close(saved_stdout);
}

/**
 * @brief Executes the builtin command and sets shell exit status.
 * @param shell The shell context.
 * @param cmd The command to execute.
 * @return The exit code from the builtin function, or 1 if no builtin found.
 */
int	s_execute_and_set_status(t_shell *shell, t_command *cmd)
{
	int				exit_code;
	t_builtin_func	func;

	exit_code = 1;
	if (apply_redirections(cmd) == 0)
	{
		func = find_builtin(cmd->args[0]);
		if (func)
		{
			exit_code = func(shell, cmd->args);
		}
	}
	shell->exit_status = exit_code;
	return (exit_code);
}

/**
 * @brief Handles pipe creation for a command if necessary.
 * @param p Pipe file descriptors array.
 * @param is_pipe Flag indicating if the command is part of a pipe.
 * @return 0 on success, -1 on pipe failure.
 */
int	s_handle_pipe_creation(int *p, int is_pipe)
{
	if (is_pipe)
	{
		if (pipe(p) == -1)
		{
			perror("minishell: pipe failed");
			return (-1);
		}
	}
	return (0);
}

/**
 * @brief Handles fork failure, closing pipe FDs if applicable.
 * @param p Pipe file descriptors array.
 * @return -1 to indicate fork failure.
 */
int	s_handle_fork_failure(int *p)
{
	perror("minishell: fork failed");
	if (p[0] != -1)
	{
		close(p[0]);
		close(p[1]);
	}
	return (-1);
}
