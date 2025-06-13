/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:25:54 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:26:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static	char	*build_unescaped_word(const char *start, size_t len)
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

static char	*find_unquoted_end(const char *pos, const char *delim)
{
	while (*pos)
	{
		if (*pos == '\\' && *(pos + 1))
		{
			pos += 2;
			continue ;
		}
		if (ft_strchr(delim, *pos) || *pos == '\'' || *pos == '"'
			|| is_token_operator(*pos))
		{
			break ;
		}
		pos++;
	}
	return ((char *)pos);
}

int	process_unquoted_segment(char **builder, char **pos, const char *delim)
{
	char	*start;
	char	*end;
	char	*part;

	start = *pos;
	end = find_unquoted_end(start, delim);
	if (end > start)
	{
		part = build_unescaped_word(start, end - start);
		if (!part)
		{
			perror("minishell: malloc failed in unquoted segment");
			return (0);
		}
		if (!append_to_builder(builder, part))
		{
			free(part);
			return (0);
		}
	}
	*pos = end;
	return (1);
}
