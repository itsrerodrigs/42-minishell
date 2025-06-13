/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:32:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 16:51:34 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a syntax error message to stderr.
 */
int	syntax_error(const char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token, 2);
		ft_putendl_fd("`", 2);
	}
	else
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`",
			2);
	return (258);
}

/**
 * @brief Checks if a token is a word type (command, arg, filename).
 */
int	is_token_cmd(t_token *token)
{
	if (token && (token->type == TOKEN_WORD
			|| token->type == TOKEN_SINGLE_QUOTED
			|| token->type == TOKEN_DOUBLE_QUOTED))
		return (1);
	return (0);
}

/**
 * @brief Checks if a token is a redirection operator.
 */
int	is_token_redir(t_token *token)
{
	if (token && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND
			|| token->type == TOKEN_HEREDOC))
		return (1);
	return (0);
}
