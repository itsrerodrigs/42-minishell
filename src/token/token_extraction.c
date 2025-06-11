/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extraction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 11:31:23 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:49:08 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parser.h"

/*
 ** @brief: Frees all tokens in the linked list.
 ** @param: head - Pointer to the first token in the list.
 ** @return: None (void function).
 */
void free_tokens(t_token *head)
{
    t_token *tmp;
    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

/*
 ** @brief: Creates a new token with the given value and type.
 ** @param: buf - Token value string.
 ** @param: type - Type of token (command, pipe, redirection, etc.).
 ** @return: Pointer to newly allocated `t_token` structure.
 */
t_token *create_token(char *buf, t_token_type type)
{
    t_token *new_token;

    if (!buf)
        return (NULL);

    new_token = malloc(sizeof(t_token));
    if (!new_token)
    {
        free(buf);
        return (NULL);
    }
    new_token->value = strdup(buf);
    new_token->type = type;
    new_token->next = NULL;

    return (new_token);
}

static t_token *extract_tokens(char **saveptr, t_shell *shell) {
    t_token *head;
    t_token *current;
    t_token *new_token; // This will directly receive the t_token*

    head = NULL;
    current = NULL;
    while ((new_token = ft_get_next_token(NULL, DELIM, saveptr, shell))) { // Use new tokenizer function
        if (!new_token)
            return (free_tokens(head), NULL);
        if (!head)
            head = new_token;
        else
            current->next = new_token;
        current = new_token;
    }
    return (head);
}

/*
 ** @brief: Tokenizes the input string and returns a linked list of tokens.
 ** @param: input - Raw input string to tokenize.
 ** @return: Pointer to the first token in the linked list.
 */
t_token *get_tokens(char *input, t_shell *shell)
{
    char *saveptr;
    
    if (!input) 
        return (NULL);
    saveptr = input;
    return (extract_tokens(&saveptr, shell));
}
