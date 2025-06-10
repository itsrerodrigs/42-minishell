/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:23:20 by marielidias       #+#    #+#             */
/*   Updated: 2025/06/10 14:41:56 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strdup(const char *src)
// {
// 	char	*dest;
// 	int		index;
// 	int		len;

// 	len = (ft_strlen(src) + 1);
// 	dest = (char *)malloc(len);
// 	if (dest == NULL)
// 		return (NULL);
// 	index = 0;
// 	while (src[index] != '\0')
// 	{
// 		dest[index] = src[index];
// 		index++;
// 	}
// 	dest[index] = '\0';
// 	return (dest);
// }

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		index;
	int		len;

	len = (ft_strlen(src) + 1);
	dest = (char *)malloc(len);
	if (dest == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
