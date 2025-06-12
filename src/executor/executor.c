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
 * @brief Executes a single, non-piped command. This can be a builtin or
 * an external program. This function is blocking and waits for the command
 * to complete.
 * @param shell The main shell struct.
 * @param cmd The single command to execute.
 */
static void	execute_simple_command(t_shell *shell, t_command *cmd)
{
	shell->current_cmd = cmd;

	if (cmd->args && cmd->args[0] && ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(shell, cmd->args);
	else if (!exec_builtin(shell))
		exec_external(shell, cmd->args);
}

/**
 * @brief The main execution controller. It iterates through the command list
 * and decides whether to execute commands sequentially (for ';') or
 * concurrently in a pipeline (for '|').
 */
void	ft_exec(t_shell *shell)
{
	t_command	*cmd;

	if (!shell || !shell->current_cmd)
		return ;
	if (process_all_heredocs(shell->current_cmd, shell) != 0)
		return ;

	cmd = shell->current_cmd;
	while (cmd)
	{
		if (cmd->is_pipe)
		{
			exec_pipeline(shell, cmd);
			while (cmd && cmd->is_pipe)
				cmd = cmd->next;
		}
		else
			execute_simple_command(shell, cmd);
		if (cmd)
			cmd = cmd->next;
	}
}
