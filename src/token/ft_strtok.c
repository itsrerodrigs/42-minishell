/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:59 by marieli           #+#    #+#             */
/*   Updated: 2025/05/02 14:47:27 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	skip_delim(char **saveptr, const char *delim)
{
	while (**saveptr && ft_strchr(delim, **saveptr))
		(*saveptr)++;
}

char *ft_strtok(char *str, const char *delim, char **saveptr)
{
    char *start;
        
    if (!saveptr || !delim || (str && !*saveptr))
        return (NULL);
    if (str)
        *saveptr = str;
    skip_delim(saveptr, delim);    
    if (**saveptr == '\0')
        return (NULL);
        
    if (**saveptr == '\'' || **saveptr == '"')
        return handle_quotes(saveptr, **saveptr);
    
    start = *saveptr;
    while (**saveptr)
    {
        if (ft_strchr(delim, **saveptr))
            break;
        (*saveptr)++;
    }    
    if (**saveptr)
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    return (start);
}
