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


// /**
//  * @brief Iterates through the string to find the matching closing quote.
//  */
// static char	*find_closing_quote(char *start, char quote_char)
// {
// 	char *end;

// 	end = start;
// 	while (*end)
// 	{
// 		if (*end == '\\' && (*(end + 1) == quote_char))
// 		{
// 			end += 2;
// 			continue ;
// 		}
// 		if (*end == quote_char)
// 			break ;
// 		end++;
// 	}
// 	return (end);
// }

// /**
//  * @brief Extracts a quoted substring from the input.
//  */
// char	*extract_quoted(char **saveptr, char quote_char)
// {
// 	char *start_content;
// 	char *end_content;
// 	char *extracted_copy;
// 	size_t len;

// 	(*saveptr)++;
// 	start_content = *saveptr;
// 	end_content = find_closing_quote(start_content, quote_char);
// 	if (*end_content == '\0')
// 	{
// 		ft_putendl_fd("minishell: error: unmatched quote", STDERR_FILENO);
// 		*saveptr = NULL;
// 		return (NULL);
// 	}
// 	len = end_content - start_content;
// 	extracted_copy = ft_strndup(start_content, len);
// 	if (!extracted_copy)
// 	{
// 		perror("minishell: ft_strndup failed");
// 		*saveptr = NULL;
// 		return (NULL);
// 	}
// 	*saveptr = end_content + 1;
// 	return (extracted_copy);
// }

// /**
//  * @brief Handles a quote token, creating a WORD or SINGLE_QUOTED token.
//  */
// t_token	*handle_quotes(char **saveptr, char quote_char, t_shell *shell)
// {
// 	char *start;
// 	char *expanded;
// 	t_token *new_token;

// 	if (!saveptr || !*saveptr || **saveptr != quote_char)
// 		return (NULL);
// 	start = extract_quoted(saveptr, quote_char);
// 	if (!start)
// 		return (NULL);
// 	if (quote_char == '"')
// 	{
// 		expanded = expand_variables(start, shell->envp, shell->exit_status);
// 		if (!expanded)
// 		{
// 			p("Error: Memory allocation failed during variable expansion.\n");
// 			return (NULL);
// 		}
// 		new_token = create_token(expanded, TOKEN_WORD);
// 	}
// 	else
// 		new_token = create_token(start, TOKEN_SINGLE_QUOTED);
// 	return (new_token);
// }


/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* quotes.c                                           :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/05/09 13:15:45 by mmariano          #+#    #+#             */
/* Updated: 2025/06/11 17:30:00 by marieli          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character can be escaped by a backslash in double quotes.
 */
static int	is_double_quote_escapable(char c)
{
	return (c == '$' || c == '"' || c == '\\');
}

/**
 * @brief Builds a new string from the quoted content, processing escape sequences.
 */
static char	*build_unescaped_string(const char *start, size_t len, char q_type)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (q_type == '"' && start[i] == '\\'
			&& is_double_quote_escapable(start[i + 1]))
		{
			new_str[j++] = start[i + 1];
			i += 2;
		}
		else
		{
			new_str[j++] = start[i];
			i++;
		}
	}
	new_str[j] = '\0';
	return (new_str);
}

/**
 * @brief Finds the matching closing quote for a given opening quote.
 */
static char	*find_closing_quote(char *start, char quote_char)
{
	char	*end;

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
 * @brief Extracts and unescapes the content of a quoted string.
 */
char	*extract_quoted(char **saveptr, char quote_char)
{
	char	*start_content;
	char	*end_content;
	char	*processed_copy;
	size_t	len;

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
	processed_copy = build_unescaped_string(start_content, len, quote_char);
	if (!processed_copy)
	{
		perror("minishell: malloc failed");
		*saveptr = NULL;
		return (NULL);
	}
	*saveptr = end_content + 1;
	return (processed_copy);
}

/**
 * @brief Handles a quote token, creating a WORD or SINGLE_QUOTED token.
 */
t_token	*handle_quotes(char **saveptr, char quote_char, t_shell *shell)
{
	char	*start;
	char	*expanded;
	t_token	*new_token;

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
			ft_putendl_fd("Error: expansion failed", STDERR_FILENO);
			return (NULL);
		}
		new_token = create_token(expanded, TOKEN_WORD);
		free(start);
	}
	else
		new_token = create_token(start, TOKEN_SINGLE_QUOTED);
	return (new_token);
}
