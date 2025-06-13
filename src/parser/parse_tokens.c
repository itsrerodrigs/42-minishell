/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:36:16 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 15:36:59 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	build_and_add_redir(t_command *cmd, t_token *redir_op, int source_fd)
{
	t_redir_type	type;
	t_token			*filename;
	int				expand;

	filename = redir_op->next;
	if (!filename || !is_token_cmd(filename))
	{
		syntax_error("newline");
		return (0);
	}
	type = get_redir_type(redir_op);
	if (source_fd == -1)
	{
		if (type == REDIR_IN || type == REDIR_HEREDOC)
			source_fd = STDIN_FILENO;
		else
			source_fd = STDOUT_FILENO;
	}
	if (filename->type != TOKEN_SINGLE_QUOTED)
		expand = 1;
	else
		expand = 0;
	if (!add_redir(cmd, source_fd, type, filename->value, expand))
		return (0);
	return (1);
}

t_command	*handle_redirection(t_command *cmd, t_token **tok_ptr)
{
	t_token	*redir_op;
	t_token	*filename_tok;
	int		source_fd;

	source_fd = -1;
	redir_op = *tok_ptr;
	if ((*tok_ptr)->type == TOKEN_WORD)
	{
		source_fd = ft_atoi((*tok_ptr)->value);
		redir_op = (*tok_ptr)->next;
	}
	if (!build_and_add_redir(cmd, redir_op, source_fd))
		return (NULL);
	filename_tok = redir_op->next;
	*tok_ptr = filename_tok->next;
	return (cmd);
}

t_command	*handle_separator(t_command *cmd, t_token **tok_ptr)
{
	t_command	*next_cmd;

	if ((*tok_ptr)->type == TOKEN_PIPE)
		cmd->is_pipe = 1;
	next_cmd = new_command(cmd);
	*tok_ptr = (*tok_ptr)->next;
	return (next_cmd);
}

int	process_token(t_command **current_cmd, t_token **tok, t_shell *shell)
{
	if (is_redir_token_group(*tok))
	{
		if (!handle_redirection(*current_cmd, tok))
			return (1);
	}
	else if ((*tok)->type == TOKEN_PIPE || (*tok)->type == TOKEN_SEMICOLON)
	{
		*current_cmd = handle_separator(*current_cmd, tok);
		if (!*current_cmd)
			return (1);
	}
	else if (is_token_cmd(*tok))
	{
		handle_word_token(*current_cmd, *tok, shell);
		*tok = (*tok)->next;
	}
	else
	{
		syntax_error((*tok)->value);
		return (1);
	}
	return (0);
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
		if (process_token(&current_cmd, &tok, shell))
		{
			free_commands(cmd_list);
			return (NULL);
		}
	}
	if (cmd_list->cmd == NULL && cmd_list->redirs == NULL)
	{
		free_commands(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}
