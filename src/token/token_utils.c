/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:48:50 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 15:56:26 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_token_segment(char **builder, char **pos, const char *delim)
{
	int	status;

	status = 0;
	if (**pos == '\'' || **pos == '"')
	{
		if (!process_quoted_segment(builder, pos))
			status = -1;
	}
	else if (ft_strchr(delim, **pos) || is_token_operator(**pos))
		status = 1;
	else
	{
		if (!process_unquoted_segment(builder, pos, delim))
			status = -1;
	}
	return (status);
}

char	*extract_next_token(char **saveptr, const char *delim)
{
	char	*token_builder;
	char	*current_pos;
	int		status;

	if (!saveptr || !*saveptr || !delim)
		return (NULL);
	token_builder = ft_strdup("");
	if (!token_builder)
	{
		*saveptr = NULL;
		return (NULL);
	}
	current_pos = *saveptr;
	status = 0;
	while (*current_pos && status == 0)
		status = build_token_segment(&token_builder, &current_pos, delim);
	*saveptr = current_pos;
	if (*token_builder == '\0' || status == -1)
	{
		free(token_builder);
		return (NULL);
	}
	return (token_builder);
}
