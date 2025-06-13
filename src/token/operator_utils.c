/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:55:36 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:25:38 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_token_type	get_single_char_op_type(char c)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	if (c == ';')
		return (TOKEN_SEMICOLON);
	return (TOKEN_WORD);
}

t_token	*extract_operator_token(char **saveptr)
{
	size_t			len;
	t_token_type	type;
	char			*op_value;

	type = get_multichar_op(*saveptr, &len);
	if (type == TOKEN_WORD)
	{
		type = get_single_char_op_type(**saveptr);
		if (type == TOKEN_WORD)
			return (NULL);
		len = 1;
	}
	op_value = ft_strndup(*saveptr, len);
	if (!op_value)
		return (NULL);
	*saveptr += len;
	return (create_token_with_fd(op_value, type, -1));
}
