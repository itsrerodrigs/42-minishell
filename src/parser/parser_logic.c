/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:47:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 13:01:13 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "parser.h" 
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

t_token	*parse_redirection(t_command *cmd, t_token *token)
{
	t_token			*filename_token;
	t_redir_type	type;
	int				expand;
	int				source_fd;
	t_redir_data	redir_info;

	filename_token = token->next;
	if (!filename_token || !is_token_cmd(filename_token))
	{
		syntax_error("newline");
		return (NULL); // Signal a syntax error
	}
	if (token->type == TOKEN_REDIR_IN)
		type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		type = REDIR_OUT;
	else if (token->type == TOKEN_APPEND)
		type = REDIR_APPEND;
	else // TOKEN_HEREDOC
		type = REDIR_HEREDOC;
	
	// Set the default source FD for simple redirections
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		source_fd = STDIN_FILENO; // Default for < and << is 0
	else
		source_fd = STDOUT_FILENO; // Default for > and >> is 1

	expand = (filename_token->type != TOKEN_SINGLE_QUOTED);
	
	redir_info.source_fd = source_fd;
	redir_info.type = type;
	redir_info.fname = filename_token->value;
	redir_info.expand = expand;
	// This is the corrected call with all 5 arguments
	if (!add_redir(cmd, &redir_info))
		return (NULL); // Signal an allocation error
		
	return (filename_token->next);
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
