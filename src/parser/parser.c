/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:34 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 14:48:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


/**
 * @brief Processes a single token during the parsing phase.
 */
static int	process_one_token(t_command **current, t_token **tokens,
		t_shell *shell)
{
	int	status;

	status = 0;
	if (is_token_cmd(*tokens))
	{
		if (!handle_word_token(*current, *tokens, shell))
			status = -1;
	}
	else if (is_token_redir(*tokens))
	{
		if (!parse_redirection(*current, tokens))
			status = -1;
	}
	else if ((*tokens)->type == TOKEN_PIPE
		|| (*tokens)->type == TOKEN_SEMICOLON)
	{
		if (handle_special_token(current, *tokens) != 0)
			status = -1;
	}
	else
	{
		syntax_error((*tokens)->value);
		status = -1;
	}
	return (status);
}

/**
 * @brief Parses a list of tokens into a structured linked list of commands.
 */
t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*cmd_list;
	t_command	*current;
	t_token		*head;
	int			error;

	head = tokens;
	expand_token_list(head, shell);
	cmd_list = init_command();
	if (!cmd_list)
		return (NULL);
	current = cmd_list;
	error = 0;
	while (head != NULL && head->type != TOKEN_EOF && error == 0)
	{
		if (process_one_token(&current, &head, shell) != 0)
			error = 1;
		head = head->next;
	}
	if (error)
	{
		free_commands(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
