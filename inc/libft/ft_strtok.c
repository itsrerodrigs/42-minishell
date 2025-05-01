/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:59 by marieli           #+#    #+#             */
/*   Updated: 2025/05/01 16:38:44 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	skip_delim(char **saveptr, const char *delim)
{
	while (**saveptr && strchr(delim, **saveptr))
		(*saveptr)++;
}

static int	handle_quotes(char **saveptr, char *quote_char)
{
	if (**saveptr == *quote_char)
	{
		*quote_char = '\0';
		return (0);
	}
	return (1);
}

static int	check_for_quotes(char **saveptr, char *quote_char)
{
	if (**saveptr == '\'' || **saveptr == '"')
	{
		*quote_char = **saveptr;
		return (1);
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim, char **saveptr)
{
	char	*start;
	char	quote_char = '\0';

	if (!saveptr || !delim || (str && !*saveptr))
		return (NULL);
	if (str)
		*saveptr = str;
	skip_delim(saveptr, delim);
	if (**saveptr == '\0')
		return (NULL);
	start = *saveptr;
	while (**saveptr)
	{
		if ((quote_char && !handle_quotes(saveptr, &quote_char)) ||
			(!quote_char && (check_for_quotes(saveptr, &quote_char) ||
			strchr(delim, **saveptr))))
			break;
		(*saveptr)++;
	}
	if (**saveptr)
		**saveptr = '\0';
	printf("Token extracted: \"%s\"\n", start);
	return (start);
}
