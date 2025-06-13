/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/05/14 20:36:14 by marieli           #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "tokens.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Token: %s | Type: %d\n", current->value, current->type);
		current = current->next;
	}
}

void	cleanup_input(t_token *input)
{
	if (!input)
		return ;
	if (input->value)
		free(input->value);
	free(input);
}
