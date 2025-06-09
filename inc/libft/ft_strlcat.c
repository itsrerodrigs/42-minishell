/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:48 by marielidias       #+#    #+#             */
/*   Updated: 2025/06/09 18:07:55 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t dlen;
    size_t slen;
    char *d;    
    const char *s; 
    size_t n;

    dlen = 0;   
    slen = ft_strlen(src); 
    d = dst;    
    s = src; 
    n = size;
    while (n-- != 0 && *d != '\0')
        d++;
    dlen = d - dst; 
    if (dlen == size)
        return (dlen + slen);
    n = size - dlen;
    while (*s != '\0' && n > 1)
    {
        *d++ = *s++;
        n--;
    }
    *d = '\0'; 
    return (dlen + slen);
}
