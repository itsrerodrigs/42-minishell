/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:04:21 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/22 17:17:16 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char	*new_string;
	size_t	lens1;
	size_t	lens2;

	if (str1)
		lens1 = ft_strlen(str1);
	else
		lens1 = 0;
	lens2 = ft_strlen(str2);
	new_string = malloc(lens1 + lens2 + 1);
	if (!new_string)
		return (NULL);
	if (str1)
	{
		ft_strlcpy(new_string, str1, lens1 + 1);
		free(str1);
	}
	ft_strlcpy(new_string + lens1, str2, lens2 + 1);
	return (new_string);
}
