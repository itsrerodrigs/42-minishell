/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:57 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 12:58:43 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

/**
 * @brief Initializes a new, empty command structure.
 */
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->is_pipe = 0;
	cmd->heredoc_pipe_read_fd = -1;
	cmd->prev_pipe_read_fd = -1;
	return (cmd);
}

/**
 * @brief Adds an argument to the command's argument list.
 */
int	add_arg(t_command *cmd, char *arg)
{
	char	**new_args;
	int		count;
	int		i;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

int	add_redir(t_command *cmd, t_redir_data *data)
{
	t_redirect	*new_redir;
	t_redirect	*last;

	new_redir = malloc(sizeof(t_redirect));
	if (!new_redir)
		return (0);
	new_redir->source_fd = data->source_fd;
	new_redir->type = data->type;
	new_redir->filename = ft_strdup(data->fname);
	new_redir->expand_heredoc = data->expand;
	new_redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_redir;
	else
	{
		last = cmd->redirs;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
	return (1);
}

/**
 * @brief Handles a token as either the main command or a subsequent argument.
 */
int	handle_cmd_or_arg(t_command *cmd, t_token *token)
{
	if (!cmd->cmd)
	{
		cmd->cmd = ft_strdup(token->value);
		if (!cmd->cmd)
			return (0);
		return (add_arg(cmd, token->value));
	}
	else
		return (add_arg(cmd, token->value));
}

/**
 * @brief Creates a new command node and links it to the current command.
 */
t_command	*new_command(t_command *current)
{
	current->next = init_command();
	return (current->next);
}
