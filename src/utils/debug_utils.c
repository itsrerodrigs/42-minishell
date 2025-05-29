/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:36:14 by marieli           #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parsing.h"


/*
 ** @brief: Prints all tokens in the linked list.
 ** @param: head - Pointer to the first token in the list.
 ** @return: None (void function).
 */
void print_tokens(t_token *head)
{
    t_token *current = head;

    while (current)
    {
        printf("Token: %s | Type: %d\n", current->value, current->type);
        current = current->next;
    }
}

/*
 ** @brief: Cleans up allocated memory for input.
 ** @param input: Pointer to the input token.
 */
void cleanup_input(t_token *input)
{
    if (!input)
        return;

    if (input->value)
        free(input->value);
    free(input);
}
