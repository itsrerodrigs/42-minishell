/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 19:51:10 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 13:13:17 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	print_commands(t_command *cmd)
{
	t_redirect	*redir;
	int			i;

	while (cmd)
	{
		printf("Command: %s\n", cmd->cmd);
		i = 0;
		if (cmd ->args && cmd->args[i])
		{
			i++;
			printf("  Arg[%d]: %s\n", i, cmd->args[i]);
		}
		redir = cmd->redirs;
		while (redir)
		{
			printf("  Redir (%d): %s\n", redir->type, redir->filename);
			redir = redir->next;
		}
		if (cmd->is_pipe)
			printf("  | Pipe to next command\n");
		cmd = cmd->next;
	}
}
