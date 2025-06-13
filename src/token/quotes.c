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

static int	is_double_quote_escapable(char c)
{
	return (c == '$' || c == '"' || c == '\\');
}

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

static char	*find_closing_quote(char *start, char quote_char)
{
	char	*ptr;

	ptr = start;
	while (*ptr)
	{
		if (quote_char == '"' && *ptr == '\\')
		{
			if (*(ptr + 1))
				ptr += 2;
			else
				ptr++;
		}
		else if (*ptr == quote_char)
			return (ptr);
		else
			ptr++;
	}
	return (ptr);
}

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
			return (NULL);
		new_token = create_token(expanded, TOKEN_WORD);
		free(start);
		free(expanded);
	}
	else
	{
		new_token = create_token(start, TOKEN_SINGLE_QUOTED);
		free(start);
	}
	return (new_token);
}
