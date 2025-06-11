/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:06 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Finds the executable path and executes the command. Exits on failure.
 */
void	exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path)
{
	char	*cmd_path;

	if (caller_cmd_path)
		cmd_path = caller_cmd_path;
	else
	{
		cmd_path = find_executable(cmd->cmd, shell);
		if (!cmd_path)
		{
			ft_putstr_fd(cmd->cmd, STDERR_FILENO);
			ft_putendl_fd(": command not found", STDERR_FILENO);
			exit(127);
		}
	}
	execve(cmd_path, cmd->args, shell->envp);
	perror("minishell: execve failed");
	if (!caller_cmd_path)
		free(cmd_path);
	exit(EXIT_FAILURE);
}
