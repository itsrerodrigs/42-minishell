/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:30:48 by marielidias       #+#    #+#             */
/*   Updated: 2025/06/12 10:56:24 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = 0;
	slen = ft_strlen(src);
	while (dlen < size && dst[dlen] != '\0')
		dlen++;
	i = 0;
	while (dlen + i + 1 < size && src[i] != '\0')
	{
		dst[dlen + i] = src[i];
			i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}
