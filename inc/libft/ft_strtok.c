/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:18:59 by marieli           #+#    #+#             */
/*   Updated: 2025/04/23 17:20:27 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strtok(char *str, const char *delim, char **saveptr)
{
    char *start;

    if (str != NULL)
        *saveptr = str;
    if (*saveptr == NULL)
        return (NULL);
        
    while (**saveptr && ft_strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr == '\0')
        return (NULL);

    start = *saveptr;
    while (**saveptr && !ft_strchr(delim, **saveptr))
        (*saveptr)++;
    if (**saveptr)
    {
        **saveptr = '\0';
        (*saveptr)++;
    }

    return (start);
}