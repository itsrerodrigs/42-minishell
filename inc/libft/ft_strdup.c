/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:23:20 by marielidias       #+#    #+#             */
/*   Updated: 2025/06/09 19:15:47 by mmariano         ###   ########.fr       */
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

	len = (ft_strlen(src) + 1); // Calculate length, including null terminator
	dest = (char *)malloc(len); // Attempt to allocate memory
	if (dest == NULL) // If malloc fails
	{
        errno = ENOMEM; // <<< CRITICAL: Set errno to indicate "Out of memory"
		return (NULL);  // Return NULL to signal failure
	}
	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0'; // Null-terminate the duplicated string
	return (dest);      // Return pointer to the duplicated string
}