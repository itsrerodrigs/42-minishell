/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:29:00 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 16:39:06 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	s_get_redir_fd(t_redir_type type, int source_fd_val)
{
	if (source_fd_val == -1)
	{
		if (type == REDIR_IN || type == REDIR_HEREDOC)
			return (STDIN_FILENO);
		else
			return (STDOUT_FILENO);
	}
	return (source_fd_val);
}

static int	s_populate_and_add_redir(t_command *current_cmd, t_token *redir_op,
		t_token *filename, int source_fd_val)
{
	t_redir_data	redir_info;

	redir_info.type = get_redir_type(redir_op);
	redir_info.source_fd = s_get_redir_fd(redir_info.type, source_fd_val);
	redir_info.expand = (filename->type != TOKEN_SINGLE_QUOTED);
	redir_info.fname = filename->value;
	if (!add_redir(current_cmd, &redir_info))
		return (0);
	return (1);
}

t_token	*s_handle_redirection_token(t_command *current_cmd, t_token *tok)
{
	t_token	*redir_op;
	t_token	*filename;
	int		source_fd_val;

	redir_op = tok;
	source_fd_val = -1;
	if (tok->type == TOKEN_WORD && is_all_digits(tok->value))
	{
		source_fd_val = ft_atoi(tok->value);
		redir_op = tok->next;
	}
	filename = redir_op->next;
	if (!filename || !is_token_cmd(filename))
	{
		syntax_error("newline");
		return (NULL);
	}
	if (!s_populate_and_add_redir(current_cmd, redir_op,
			filename, source_fd_val))
		return (NULL);
	return (filename->next);
}
