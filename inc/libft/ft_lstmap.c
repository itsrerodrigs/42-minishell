/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:16:01 by marieli           #+#    #+#             */
/*   Updated: 2025/05/22 17:14:33 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	if (lst == NULL)
		return (NULL);
	new_lst = ft_lstnew(f(lst->data));
	if (new_lst == NULL)
		return (NULL);
	new_elem = new_lst;
	lst = lst->next;
	while (lst)
	{
		new_elem->next = ft_lstnew(f(lst->data));
		if (new_elem->next == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		new_elem = new_elem->next;
		lst = lst->next;
	}
	return (new_lst);
}
