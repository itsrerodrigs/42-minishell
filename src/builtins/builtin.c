/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 16:03:50 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


bool is_builtin_parent_executable(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]) +1) ||
		ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]) + 1) ||
		ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]) + 1) ||
		ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]) + 1))
		{
			return (!cmd->is_pipe && cmd->prev_pipe_read_fd == -1);
		}
		return (false);
}
