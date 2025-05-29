/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:40:41 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/22 17:17:48 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	index;
	size_t	sub_len;

	index = 0;
	if (*sub == '\0')
		return ((char *)str);
	sub_len = 0;
	while (sub[sub_len] != '\0')
		sub_len++;
	while (str[index] != '\0' && index + sub_len <= len)
	{
		if (str[index] == sub[0] && ft_memcmp(str + index, sub, sub_len) == 0)
			return ((char *)(str + index));
		index++;
	}
	return (NULL);
}
