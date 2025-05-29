/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:16:05 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/22 17:15:00 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;
	size_t		index;

	str = (const char *)s;
	index = 0;
	while (index < n)
	{
		if (str[index] == (char)c)
			return ((void *)(str + index));
		index++;
	}
	return (NULL);
}
