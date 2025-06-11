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
 * @brief Processes an unquoted segment, appending it to the builder.
 */
int	process_unquoted_segment(char **builder, char **pos, const char *delim)
{
	char	*start;
	char	*end;
	char	*part;

	start = *pos;
	end = *pos;
	while (*end && !ft_strchr(delim, *end) && *end != '\'' && *end != '"'
		&& !is_token_operator(*end))
	{
		end++;
	}
	if (end > start)
	{
		part = ft_strndup(start, end - start);
		if (!part)
		{
			perror("minishell: ft_strndup failed");
			return (0);
		}
		if (!append_to_builder(builder, part))
			return (0);
	}
	*pos = end;
	return (1);
}
