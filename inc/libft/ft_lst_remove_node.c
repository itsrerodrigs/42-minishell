/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:15:10 by marieli           #+#    #+#             */
/*   Updated: 2025/05/22 17:13:49 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	remove_node(t_list **head, t_list *node_to_remove)
{
	t_list	*temp;

	if (!head || !*head || !node_to_remove)
		return (0);
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		free(node_to_remove);
		return (1);
	}
	temp = *head;
	while (temp && temp->next != node_to_remove)
		temp = temp->next;
	if (temp && temp->next == node_to_remove)
	{
		temp->next = node_to_remove->next;
		free(node_to_remove);
		return (1);
	}
	return (0);
}
