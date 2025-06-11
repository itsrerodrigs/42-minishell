/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:02:39 by marieli           #+#    #+#             */
/*   Updated: 2025/06/11 11:02:39 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


/**
 * @brief Iterates through the string to find the matching closing quote.
 */
static char	*find_closing_quote(char *start, char quote_char)
{
	char *end;

	end = start;
	while (*end)
	{
		if (*end == '\\' && (*(end + 1) == quote_char))
		{
			end += 2;
			continue ;
		}
		if (*end == quote_char)
			break ;
		end++;
	}
	return (end);
}

/**
 * @brief Extracts a quoted substring from the input.
 */
char	*extract_quoted(char **saveptr, char quote_char)
{
	char *start_content;
	char *end_content;
	char *extracted_copy;
	size_t len;

	(*saveptr)++;
	start_content = *saveptr;
	end_content = find_closing_quote(start_content, quote_char);
	if (*end_content == '\0')
	{
		ft_putendl_fd("minishell: error: unmatched quote", STDERR_FILENO);
		*saveptr = NULL;
		return (NULL);
	}
	len = end_content - start_content;
	extracted_copy = ft_strndup(start_content, len);
	if (!extracted_copy)
	{
		perror("minishell: ft_strndup failed");
		*saveptr = NULL;
		return (NULL);
	}
	*saveptr = end_content + 1;
	return (extracted_copy);
}

/**
 * @brief Handles a quote token, creating a WORD or SINGLE_QUOTED token.
 */
t_token	*handle_quotes(char **saveptr, char quote_char, t_shell *shell)
{
	char *start;
	char *expanded;
	t_token *new_token;

	if (!saveptr || !*saveptr || **saveptr != quote_char)
		return (NULL);
	start = extract_quoted(saveptr, quote_char);
	if (!start)
		return (NULL);
	if (quote_char == '"')
	{
		expanded = expand_variables(start, shell->envp, shell->exit_status);
		if (!expanded)
		{
			p("Error: Memory allocation failed during variable expansion.\n");
			return (NULL);
		}
		new_token = create_token(expanded, TOKEN_WORD);
	}
	else
		new_token = create_token(start, TOKEN_SINGLE_QUOTED);
	return (new_token);
}
