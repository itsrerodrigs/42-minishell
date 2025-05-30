/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:32:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 14:32:11 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parser.h"

int syntax_error(const char *token)
{
    if (token)
        fprintf(stderr, "minishell: syntax error near unexpected token `%s`\n", token);
    else
        fprintf(stderr, "minishell: syntax error near unexpected token `newline`\n");
    return (258);
}

int is_token_cmd(t_token *token)
{
    return (token
        && (token->type == TOKEN_WORD
         || token->type == TOKEN_SINGLE_QUOTED
         || token->type == TOKEN_DOUBLE_QUOTED));
}

int is_token_redir(t_token *token)
{
    return (token
        && (token->type == TOKEN_REDIR_IN
         || token->type == TOKEN_REDIR_OUT
         || token->type == TOKEN_APPEND
         || token->type == TOKEN_HEREDOC));
}
