/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:36:21 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:36:21 by mmariano         ###   ########.fr       */
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
