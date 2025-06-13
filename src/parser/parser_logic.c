/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:47:31 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:01:42 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h" 
/*
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

/* @brief Fills the t_redir_data struct based on the redirection 
 * and filename tokens.
 * @param redir_data Pointer to the t_redir_data struct to be filled.
 * @param token The redirection token (e.g., <, >, >>, <<).
 * @param filename_token The token representing the filename.
 */
static void	s_fill_redir_data(t_redir_data *redir_data, t_token *token,
		t_token *filename_token)
{
	if (token->type == TOKEN_REDIR_IN)
		redir_data->type = REDIR_IN;
	else if (token->type == TOKEN_REDIR_OUT)
		redir_data->type = REDIR_OUT;
	else if (token->type == TOKEN_APPEND)
		redir_data->type = REDIR_APPEND;
	else
		redir_data->type = REDIR_HEREDOC;
	if (redir_data->type == REDIR_IN
		|| redir_data->type == REDIR_HEREDOC)
		redir_data->source_fd = STDIN_FILENO;
	else
		redir_data->source_fd = STDOUT_FILENO;
	redir_data->expand = (filename_token->type != TOKEN_SINGLE_QUOTED);
	redir_data->fname = filename_token->value;
}

t_token	*parse_redirection(t_command *cmd, t_token *token)
{
	t_token			*filename_token;
	t_redir_data	redir_info;

	filename_token = token->next;
	if (!filename_token || !is_token_cmd(filename_token))
	{
		syntax_error("newline");
		return (NULL);
	}
	s_fill_redir_data(&redir_info, token, filename_token);
	if (!add_redir(cmd, &redir_info))
		return (NULL);
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
