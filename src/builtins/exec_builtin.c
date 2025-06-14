/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:07 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 21:54:09 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	s_save_original_fds(int *orig_stdin, int *orig_stdout)
{
	*orig_stdin = dup(STDIN_FILENO);
	*orig_stdout = dup(STDOUT_FILENO);
	if (*orig_stdin == -1 || *orig_stdout == -1)
	{
		perror("minishell: dup failed in builtin setup");
		if (*orig_stdin != -1)
			close(*orig_stdin);
		if (*orig_stdout != -1)
			close(*orig_stdout);
		return (1);
	}
	return (0);
}

static void	s_restore_fds(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

static int	s_perform_builtin_io_and_exec(t_shell *shell, t_builtin_func func)
{
	int	builtin_exit_status;

	if (apply_redirections(shell->current_cmd) != 0)
	{
		shell->exit_status = 1;
		return (-1);
	}
	builtin_exit_status = func(shell, shell->current_cmd->args);
	shell->exit_status = builtin_exit_status;
	return (1);
}

int	exec_builtin(t_shell *shell)
{
	t_builtin_func	func;
	char			*cmd;
	int				orig_stdin;
	int				orig_stdout;
	int				exec_result;

	if (!shell || !shell->current_cmd || !shell->current_cmd->args
		|| !shell->current_cmd->args[0])
		return (0);
	cmd = shell->current_cmd->args[0];
	func = find_builtin(cmd);
	if (!func)
		return (0);
	if (s_save_original_fds(&orig_stdin, &orig_stdout) != 0)
		return (0);
	exec_result = s_perform_builtin_io_and_exec(shell, func);
	s_restore_fds(orig_stdin, orig_stdout);
	if (exec_result == -1)
		return (1);
	return (1);
}
