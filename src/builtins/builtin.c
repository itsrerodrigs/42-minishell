/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/12 11:17:45 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool is_builtin_parent_executable(t_command *cmd)
{
	char *cmd_name;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);

	cmd_name = cmd->args[0];

	// The logic is now "if the command name is an exact match..."
	if (ft_strcmp(cmd_name, "cd") == 0 ||
		ft_strcmp(cmd_name, "exit") == 0 ||
		ft_strcmp(cmd_name, "export") == 0 ||
		ft_strcmp(cmd_name, "unset") == 0)
	{
		// And it is a single command (not in a pipeline)
		return (!cmd->is_pipe && cmd->prev_pipe_read_fd == -1);
	}
	return (false);
}
