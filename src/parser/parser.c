/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:34 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 16:54:20 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "tokens.h"

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

t_redir_type	get_redir_type(t_token *token)
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
		tok = s_parse_loop_iteration(&current_cmd, tok, shell, cmd_list);
		if (!tok)
		{
			break ;
		}
	}
	if (!cmd_list->cmd && !cmd_list->redirs)
		return (free_commands(cmd_list), NULL);
	return (cmd_list);
}
