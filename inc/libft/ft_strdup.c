<<<<<<< HEAD
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


=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:23:20 by marielidias       #+#    #+#             */
/*   Updated: 2025/04/28 19:03:11 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		index;
	int		len;

	len = (ft_strlen(src) + 1);
	dest = (char *)malloc(len);
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}
>>>>>>> builtins-test
