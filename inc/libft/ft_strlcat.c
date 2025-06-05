/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:48 by marielidias       #+#    #+#             */
/*   Updated: 2025/06/05 15:55:02 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
// {
// 	size_t	src_len;
// 	size_t	dest_len;

// 	src_len = ft_strlen(src);
// 	dest_len = ft_strlen(dest);
// 	if (dest_len >= destsize)
// 		dest_len = destsize;
// 	if (dest_len == destsize)
// 		return (destsize + src_len);
// 	if (src_len < (destsize - dest_len))
// 		ft_memcpy((dest + dest_len), src, (src_len + 1));
// 	else
// 	{
// 		ft_memcpy((dest + dest_len), src, (destsize - dest_len - 1));
// 		dest[destsize - 1] = '\0';
// 	}
// 	return (dest_len + src_len);
// }


// Common ft_strlcat bug example leading to 'est'
size_t ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t dlen = 0;
    size_t slen = ft_strlen(src); // Assuming ft_strlen is fine

    // Find current length of dst (dlen)
    while (dlen < size && dst[dlen] != '\0')
        dlen++;

    // This loop is often where the bug creeps in
    // If dlen is the end of the string, copying should start from dst[dlen]
    // If the loop condition or indexing is off by one, it might skip the first char.
    size_t i = 0;
    while (dlen + i + 1 < size && src[i] != '\0') // dlen + i + 1 < size is correct for space for null
    {
        dst[dlen + i] = src[i]; // <--- This should copy from src[0]
        i++;
    }
    dst[dlen + i] = '\0'; // Null-terminate

    return (dlen + slen); // Total length if no truncation
}