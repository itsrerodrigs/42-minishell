/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:59 by marieli           #+#    #+#             */
/*   Updated: 2025/05/01 19:37:37 by marieli          ###   ########.fr       */
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
    
    printf("Debug: Entering ft_strtok()\n");
    
    if (!saveptr || !delim || (str && !*saveptr))
        return (NULL);
    if (str)
        *saveptr = str;

    printf("Debug: Before skipping delimiters, saveptr -> %s\n", *saveptr);
    skip_delim(saveptr, delim);
    printf("Debug: After skipping delimiters, saveptr -> %s\n", *saveptr);
    
    if (**saveptr == '\0')
    {
        printf("Debug: saveptr is empty after skip_delim()\n");
        return (NULL);
    }
        
    if (**saveptr == '\'' || **saveptr == '"')
    {
        printf("Debug: Found quote -> %c\n", **saveptr);
        return handle_quotes(saveptr, **saveptr);
    }
    
    start = *saveptr;
    while (**saveptr)
    {
        if (ft_strchr(delim, **saveptr))
            break;
        (*saveptr)++;
    }
    printf("Debug: Token extracted -> %s\n", start);
    
    if (**saveptr)
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    return (start);
}
