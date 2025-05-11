/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:23:20 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/09 15:48:08 by mmariano         ###   ########.fr       */
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


