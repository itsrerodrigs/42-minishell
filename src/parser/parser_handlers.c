/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:14:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 16:50:55 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static t_command	*s_handle_separator_token(t_command *current_cmd,
		t_token *tok)
{
	if (!tok->next || tok->next->type == TOKEN_PIPE
		|| tok->next->type == TOKEN_SEMICOLON)
	{
		syntax_error(tok->value);
		return (NULL);
	}
	if (tok->type == TOKEN_PIPE)
		current_cmd->is_pipe = 1;
	current_cmd->next = init_command();
	if (!current_cmd->next)
		return (NULL);
	return (current_cmd->next);
}

static t_token	*s_handle_token_error(t_command *cmd_list, const char *msg)
{
	syntax_error(msg);
	free_commands(cmd_list);
	return (NULL);
}

static t_token	*s_handle_command_case(t_command **current_cmd_ptr,
		t_token *tok, t_shell *shell, t_command *cmd_list)
{
	t_token	*next_tok;

	if (!handle_word_token(*current_cmd_ptr, tok, shell))
		return (s_handle_token_error(cmd_list, "allocation error"));
	next_tok = tok->next;
	return (next_tok);
}

t_token	*s_parse_loop_iteration(t_command **current_cmd_ptr,
		t_token *tok, t_shell *shell, t_command *cmd_list)
{
	if (is_token_redir(tok) || (tok->next && is_token_redir(tok->next)
			&& is_all_digits(tok->value)))
	{
		return (s_handle_redirection_token(*current_cmd_ptr, tok));
	}
	else if (tok->type == TOKEN_PIPE || tok->type == TOKEN_SEMICOLON)
	{
		*current_cmd_ptr = s_handle_separator_token(*current_cmd_ptr, tok);
		if (!(*current_cmd_ptr))
			return (s_handle_token_error(cmd_list, tok->value));
		return (tok->next);
	}
	else if (is_token_cmd(tok))
	{
		return (s_handle_command_case(current_cmd_ptr, tok, shell, cmd_list));
	}
	return (s_handle_token_error(cmd_list, tok->value));
}
