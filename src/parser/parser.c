/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:34 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 13:43:37 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "parser.h"
#include "tokens.h"

// Helper to check if a string contains only digits.
static int	is_all_digits(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// Helper to get the redirection type from a token.
static t_redir_type	get_redir_type(t_token *token)
{
	if (token->type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (token->type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (token->type == TOKEN_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*cmd_list;
	t_command	*current_cmd;
	t_token		*tok;

	expand_token_list(tokens, shell);
	cmd_list = init_command();
	if (!cmd_list)
		return (NULL);
	current_cmd = cmd_list;
	tok = tokens;
	while (tok)
	{
		// Case 1: Handle redirections, including those with explicit FDs like 2>
		if (is_token_redir(tok) || (tok->next && is_token_redir(tok->next) && is_all_digits(tok->value)))
		{
			t_token *redir_op = tok;
			int source_fd = -1;

			if (tok->type == TOKEN_WORD) // This means we have an FD, e.g., "2"
			{
				source_fd = ft_atoi(tok->value);
				redir_op = tok->next;
			}
			t_token *filename = redir_op->next;
			if (!filename || !is_token_cmd(filename))
				return (syntax_error("newline"), free_commands(cmd_list), NULL);
			t_redir_type type = get_redir_type(redir_op);
			if (source_fd == -1)
				source_fd = (type == REDIR_IN || type == REDIR_HEREDOC) ? STDIN_FILENO : STDOUT_FILENO;
			int expand = (filename->type != TOKEN_SINGLE_QUOTED);
			if (!add_redir(current_cmd, source_fd, type, filename->value, expand))
				return (free_commands(cmd_list), NULL);
			tok = filename->next;
		}
		// Case 2: Handle pipes
		else if (tok->type == TOKEN_PIPE)
		{
			current_cmd->is_pipe = 1;
			current_cmd = new_command(current_cmd);
			tok = tok->next;
		}
		// Case 3: Handle commands, arguments, and variable assignments
		else if (is_token_cmd(tok))
		{
			// This call correctly handles assignments vs. commands
			handle_word_token(current_cmd, tok, shell);
			tok = tok->next;
		}
		else
		{
			syntax_error(tok->value);
			return (free_commands(cmd_list), NULL);
		}
	}
	// If the line was empty or only contained assignments, don't execute.
	if (cmd_list->cmd == NULL && cmd_list->redirs == NULL)
		return (free_commands(cmd_list), NULL);
	return (cmd_list);
}