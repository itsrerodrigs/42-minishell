/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:47:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 18:25:47 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/**
 * @brief Checks if a token value represents a valid variable assignment name.
 */
static int	is_valid_assignment_name(const char *value)
{
	char	*equals_pos;
	char	*c;

	equals_pos = ft_strchr(value, '=');
	if (!equals_pos || equals_pos == value)
		return (0);
	if (!ft_isalpha(value[0]) && value[0] != '_')
		return (0);
	c = (char *)value;
	while (c < equals_pos)
	{
		if (!ft_isalnum(*c) && *c != '_')
			return (0);
		c++;
	}
	return (1);
}

/**
 * @brief Handles a word token, which could be a command, argument,
	or assignment.
 */
int	handle_word_token(t_command *current_cmd, t_token *token, t_shell *shell)
{
	int	result;

	result = 0;
	if (is_valid_assignment_name(token->value))
	{
		if (add_or_update_env(&shell->envp, token->value) != 0)
			return (0);
		if (current_cmd->cmd == NULL)
			return (1);
	}
	result = handle_cmd_or_arg(current_cmd, token);
	return (result);
}

/**
 * @brief Parses a redirection token and its following filename.
 */
int	parse_redirection(t_command *cmd, t_token **token_ptr)
{
	t_token			*token;
	t_token			*next;
	t_redir_type	type;
	int				expand;

	token = *token_ptr;
	next = token->next;
	if (!next || !is_token_cmd(next))
		return (syntax_error("newline"));
	if (token->type == TOKEN_REDIR_IN)
		type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		type = REDIR_OUT;
	else if (token->type == TOKEN_APPEND)
		type = REDIR_APPEND;
	else
		type = REDIR_HEREDOC;
	expand = (next->type == TOKEN_WORD); // Expand if delimiter is an unquoted word
	if (!add_redir(cmd, type, next->value, expand))
		return (0);
	*token_ptr = next;
	return (1);
}


/**
 * @brief Handles special tokens like pipes and semicolons.
 */
int	handle_special_token(t_command **current, t_token *token)
{
	if (token->type == TOKEN_PIPE)
	{
		if (!token->next || token->next->type == TOKEN_PIPE)
			return (syntax_error("|"));
		(*current)->is_pipe = 1;
		*current = new_command(*current);
	}
	else if (token->type == TOKEN_SEMICOLON)
	{
		if (!token->next || token->next->type == TOKEN_SEMICOLON)
			return (syntax_error(";"));
		*current = new_command(*current);
	}
	return (0);
}
