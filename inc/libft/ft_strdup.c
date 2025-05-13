/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:23:20 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/12 21:19:23 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *src)
{
    size_t len = ft_strlen(src);
    char *dup = malloc(len + 1);
    char *temp;

    if (!dup)
        return (NULL);

    temp = dup;
    while (*src)
        *temp++ = *src++;
    *temp = '\0';
    return (dup); 
}


