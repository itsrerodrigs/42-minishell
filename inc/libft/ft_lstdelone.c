/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:15:39 by marieli           #+#    #+#             */
/*   Updated: 2025/05/22 17:14:14 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL)
		return (0);
	del(lst->data);
	free(lst);
	return (1);
}
