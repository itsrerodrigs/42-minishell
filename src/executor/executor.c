/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:59:36 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 14:59:36 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Processes all heredoc redirections for a list of commands.
 */
static int	process_all_heredocs(t_command *commands, t_shell *shell)
{
	t_command *current_cmd;
	t_redirect *redir_node;

	current_cmd = commands;
	while (current_cmd)
	{
		redir_node = current_cmd->redirs;
		while (redir_node)
		{
			if (redir_node->type == REDIR_HEREDOC)
			{
				current_cmd->heredoc_pipe_read_fd = process_heredoc(redir_node, shell);
				if (current_cmd->heredoc_pipe_read_fd == -1)
				{
					shell->exit_status = 1;
					return (1);
				}
			}
			redir_node = redir_node->next;
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}


/**
 * @brief Executes the current command or pipeline from the shell state.
 */
void	ft_exec(t_shell *shell)
{
	char **args;

	if (!shell || !shell->current_cmd)
		return ;
	if (process_all_heredocs(shell->current_cmd, shell) != 0)
		return ;
	args = shell->current_cmd->args;
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "exit") == 0)
		builtin_exit(shell, args);
	if (shell->current_cmd->is_pipe || shell->current_cmd->next)
		exec_pipeline(shell, shell->current_cmd);
	else if (exec_builtin(shell))
		return ;
	else
		exec_external(shell, args);
}
