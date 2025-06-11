/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:48:50 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 11:07:35 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Creates a new token with a value, type, and file descriptor.
 */
t_token	*create_token_with_fd(char *value, t_token_type type, int fd_val)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (NULL);
	}
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		free(value);
		return (NULL);
	}
	new_token->type = type;
	new_token->fd = fd_val;
	new_token->next = NULL;
	free(value);
	return (new_token);
}

/**
 * @brief Identifies multi-character operators like '>>' or '<<'.
 */
static t_token_type	get_multichar_op(const char *op_start, size_t *len)
{
	t_token_type	type;

	type = TOKEN_WORD;
	*len = 0;
	if (ft_strncmp(op_start, ">>", 2) == 0)
	{
		type = TOKEN_APPEND;
		*len = 2;
	}
	else if (ft_strncmp(op_start, "<<", 2) == 0)
	{
		type = TOKEN_HEREDOC;
		*len = 2;
	}
	return (type);
}

/**
 * @brief Extracts an operator token (e.g., |, >>, <) from the input string.
 */
t_token	*extract_operator_token(char **saveptr)
{
	size_t			len;
	t_token_type	type;
	char			*op_value;
	char			op_char;

	type = get_multichar_op(*saveptr, &len);
	if (type == TOKEN_WORD)
	{
		op_char = **saveptr;
		if (op_char == '|')
			type = TOKEN_PIPE;
		else if (op_char == '<')
			type = TOKEN_REDIR_IN;
		else if (op_char == '>')
			type = TOKEN_REDIR_OUT;
		else
			return (NULL);
		len = 1;
	}
	op_value = ft_strndup(*saveptr, len);
	if (!op_value)
		return (NULL);
	*saveptr += len;
	return (create_token(op_value, type));
}

/**

	* @brief Builds a token by processing one segment at a time (quoted or unquoted).
 */
static int	build_token_segment(char **builder, char **pos, const char *delim)
{
	int	status;

	status = 0;
	if (**pos == '\'' || **pos == '"')
	{
		if (!process_quoted_segment(builder, pos))
			status = -1;
	}
	else if (ft_strchr(delim, **pos) || is_token_operator(**pos))
		status = 1;
	else
	{
		if (!process_unquoted_segment(builder, pos, delim))
			status = -1;
	}
	return (status);
}

/**
 * @brief Extracts a complex word token, handling mixed quoted/unquoted parts.
 */
char	*extract_next_token(char **saveptr, const char *delim)
{
	char	*token_builder;
	char	*current_pos;
	int		status;

	if (!saveptr || !*saveptr || !delim)
		return (NULL);
	token_builder = ft_strdup("");
	if (!token_builder)
	{
		*saveptr = NULL;
		return (NULL);
	}
	current_pos = *saveptr;
	status = 0;
	while (*current_pos && status == 0)
		status = build_token_segment(&token_builder, &current_pos, delim);
	*saveptr = current_pos;
	if (*token_builder == '\0' || status == -1)
	{
		free(token_builder);
		return (NULL);
	}
	return (token_builder);
}
