/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:48 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/22 17:17:20 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (dest_len >= destsize)
		dest_len = destsize;
	if (dest_len == destsize)
		return (destsize + src_len);
	if (src_len < (destsize - dest_len))
		ft_memcpy((dest + dest_len), src, (src_len + 1));
	else
	{
		ft_memcpy((dest + dest_len), src, (destsize - dest_len - 1));
		dest[destsize - 1] = '\0';
	}
	return (dest_len + src_len);
}
