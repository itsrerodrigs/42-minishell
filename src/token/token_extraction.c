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
#include "../inc/parsing.h"

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
t_token *create_token(char *buf, t_id type)
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

/*
 ** @brief: Extracts tokens from the input string and stores them in a linked list.
 ** @param: saveptr - Pointer to the current tokenizer state.
 ** @return: Pointer to the first token in the linked list.
 */
t_token *extract_tokens(char **saveptr)
{
    t_token     *head;
    t_token     *current;
    t_token     *new_token;
    char        *token_str;

    head = NULL;
    current = NULL;    
    while ((token_str = ft_strtok(NULL, DELIM, saveptr)))
    {
        new_token = create_token(token_str, get_token_type(token_str));
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
 ** @brief: Determines the type of a token based on its content.
 ** @param: token_str - String representing a token.
 ** @return: Token type as `t_id` (e.g., TOKEN_PIPE, TOKEN_WORD, etc.).
 */
t_id get_token_type(char *token_str)
{
    if (!token_str) 
        return (TOKEN_WORD);
    if (!strcmp(token_str, "|")) 
        return (TOKEN_PIPE);
    if (!strcmp(token_str, "<"))   
        return (TOKEN_REDIR_IN);
    if (!strcmp(token_str, ">")) 
        return (TOKEN_REDIR_OUT);
    if (!strcmp(token_str, ">>")) 
        return (TOKEN_APPEND);
    if (!strcmp(token_str, "<<")) 
        return (TOKEN_HEREDOC);
    return (TOKEN_WORD);
}

/*
 ** @brief: Tokenizes the input string and returns a linked list of tokens.
 ** @param: input - Raw input string to tokenize.
 ** @return: Pointer to the first token in the linked list.
 */
t_token *get_tokens(char *input)
{
    char *saveptr;
    
    if (!input) 
        return (NULL);
    saveptr = input;
    return (extract_tokens(&saveptr));
}
