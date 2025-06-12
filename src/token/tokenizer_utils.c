/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* tokenizer_utils.c                                  :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/06/11 10:45:00 by marieli           #+#    #+#             */
/* Updated: 2025/06/11 10:45:00 by marieli          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Appends a segment to the token being built. Frees the segment.
 */
int	append_to_builder(char **token_builder_ptr, char *segment)
{
	size_t	current_len;
	size_t	segment_len;
	size_t	new_size;
	char	*new_builder;

	if (!segment)
		return (1);
	current_len = ft_strlen(*token_builder_ptr);
	segment_len = ft_strlen(segment);
	new_size = current_len + segment_len + 1;
	new_builder = ft_realloc(*token_builder_ptr, new_size);
	if (!new_builder)
	{
		free(segment);
		return (0);
	}
	*token_builder_ptr = new_builder;
	ft_strlcat(*token_builder_ptr, segment, new_size);
	free(segment);
	return (1);
}

/**
 * @brief Processes a quoted segment, appending its content to the builder.
 */
int	process_quoted_segment(char **builder, char **pos)
{
	char	quote_char;
	char	*content;
	char	*temp_pos;

	quote_char = **pos;
	temp_pos = *pos;
	content = extract_quoted(&temp_pos, quote_char);
	if (!content)
		return (0);
	if (!append_to_builder(builder, content))
		return (0);
	*pos = temp_pos;
	return (1);
}

/**
 * @brief Checks if a character is a shell operator.
 */
int	is_token_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/**
 * @brief Creates a new string from a segment, correctly handling and
 * removing backslash escape characters.
 * @param start The beginning of the raw string segment.
 * @param len The length of the raw string segment.
 * @return A new, malloc'd string with escapes resolved.
 */
static char *build_unescaped_word(const char *start, size_t len)
{
	char	*result;
	size_t	i;
	size_t	j;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (start[i] == '\\' && i + 1 < len)
		{
			result[j++] = start[i + 1];
			i += 2;
		}
		else
		{
			result[j++] = start[i++];
		}
	}
	result[j] = '\0';
	return (result);
}

/**
 * @brief Processes an unquoted segment, appending it to the builder.
 * This version correctly handles backslash escapes, ensuring that characters
 * like spaces can be included in a token if they are escaped.
 */
int	process_unquoted_segment(char **builder, char **pos, const char *delim)
{
	char	*start;
	char	*end;
	char	*part;

	start = *pos;
	end = *pos;
	while (*end)
	{
		// If a backslash is found, skip it and the character that follows
		if (*end == '\\' && *(end + 1))
		{
			end += 2;
			continue ;
		}
		// Stop at delimiters, quotes, or operators
		if (ft_strchr(delim, *end) || *end == '\'' || *end == '"'
			|| is_token_operator(*end))
		{
			break ;
		}
		end++;
	}
	if (end > start)
	{
		// Create the final part by processing escapes
		part = build_unescaped_word(start, end - start);
		if (!part)
		{
			perror("minishell: malloc failed in unquoted segment");
			return (0);
		}
		if (!append_to_builder(builder, part))
			return (0);
	}
	*pos = end;
	return (1);
}

