/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:02:47 by marielidias       #+#    #+#             */
/*   Updated: 2025/05/22 17:17:43 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (NULL == str1 || NULL == str2 || n <= 0)
		return (0);
	while (*str1 == *str2 && n > 0 && *str1 != '\0')
	{
		++str1;
		++str2;
		--n;
	}
	return (*str1 - *str2);
}
