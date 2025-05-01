/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/01 16:45:32 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char    **get_tokens(char *line)
{
    char            **tokens;
    char            *saveptr;
    size_t          bufsize;
    unsigned int    position;

    if (!line || !*line)
        return (NULL);

    tokens = initialize_token_array(&bufsize); /* cria um array vazio */
    if (!tokens)
        return (NULL);

    position = extract_tokens(line, &tokens, &bufsize, &saveptr); /* popula o array com os tokens */
    if (position == 0)
    {
        free_tokens(tokens);
        return (NULL);
    }
    tokens[position] = NULL;
    return (tokens);
}

char *process_token(char *token, char **saveptr)
{
    if (*token == '\'' || *token == '"')
        return (handle_quotes(saveptr, *token));
    if (strchr("|><", *token))
        return (token); /*mudar depois pra lidar com operators*/
    return (token);
}

static int add_token(char ***tokens, unsigned int count, char *token)
{
    char *processed_token;

    processed_token = ft_strdup(token);
    if (!processed_token)
    {
        free_tokens(*tokens);
        return (0);
    }
    (*tokens)[count] = processed_token;
    return (1);
}

int realloc_tokens(char ***tokens, size_t *bufsize)
{
    size_t new_size = *bufsize * 2;
    char **new_tokens = ft_realloc(*tokens, new_size * sizeof(char *));
    if (!new_tokens)
        return (0);
    *tokens = new_tokens;
    *bufsize = new_size;
    return (1);
}

unsigned int extract_tokens(char *line, char ***tokens, size_t *bufsize, char **saveptr)
{
    char *token;
    unsigned int count = 0;

    if (!line || !tokens || !*tokens || !bufsize || !saveptr || *bufsize == 0)
    {
        printf("Error: Invalid input or buffer size\n");
        return (0);
    }

    /* DEBUG: Print the input line to check if it's being passed correctly */ 
    printf("Input line: \"%s\"\n", line);
    token = ft_strtok(line, DELIM, saveptr);

    if (token)
        printf("First token: \"%s\"\n", token);

    while (token)
    {
        printf("Extracted token[%d]: \"%s\"\n", count, token);
        if (count >= *bufsize - 1 && !realloc_tokens(tokens, bufsize))
        {
            printf("Error: Memory allocation failed while resizing tokens\n");
            return (0);
        }
        if (!add_token(tokens, count++, token))
        {
            printf("Error: Failed to add token\n");
            return (0);
        }

        token = ft_strtok(NULL, DELIM, saveptr);
        if (token)
            printf("Next token: \"%s\"\n", token);
    }

    (*tokens)[count] = NULL;
    return (count);
}
