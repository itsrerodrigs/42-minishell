/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:24 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/24 18:29:25 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

char    *remove_quotes(char *merged, char quote)
{
    char    *result;

    if (merged[0] == quote && merged[ft_strlen(merged) - 1] == quote)
    {
        merged[ft_strlen(merged) - 1] = '\0';
        result = ft_strdup(merged + 1);
        free(merged);
        return (result);
    }
    return (merged);
}
char    *append_until_quote(char *merged, char quote, char **saveptr)
{
    size_t  dest_size;
    char    *next;

    dest_size = ft_strlen(merged) + 1;
    while (merged[ft_strlen(merged) - 1] != quote)
    {
        next = ft_strtok(NULL, DELIM, saveptr);
        if (!next)
        {
            break;
        }
        dest_size += ft_strlen(next) + 1;
        merged = realloc(merged, dest_size);
        if (!merged)
        {
            return (NULL);
        }
        ft_strlcat(merged, " ", dest_size);
        ft_strlcat(merged, next, dest_size);
    }
    return (merged);
}

char    *merge_quotes(char *token, char quote)
{
    size_t  dest_size;
    char    *merged;

    dest_size = ft_strlen(token) + 1;
    merged = ft_malloc(dest_size);
    if (!merged)
    {
        return (NULL);
    }

    ft_strlcpy(merged, token, ft_strlen(token) + 1);
    merged = ft_malloc(dest_size);
    if (!merged)
    {
        return (NULL);
    }
    ft_strlcpy(merged, token, dest_size);    
    free(merged);
    return (remove_quotes(merged, quote));
}

char *handle_single_quotes(char **saveptr)
{
    char *start;

    start = ++(*saveptr); // Skip the opening single quote
    if (*start == '\0' || ft_strchr(start, '\'') == NULL)
    {
        return (merge_quotes(start - 1, '\'')); // Pass opening quote
    }

    while (**saveptr && **saveptr != '\'')
        (*saveptr)++;

    if (**saveptr == '\'')
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    else
    {
        printf("Error: Unclosed single quote.\n");
        return (NULL);
    }
    return (start);
}

char *handle_double_quotes(char **saveptr)
{
    char *start;

    start = ++(*saveptr); // Skip the opening double quote
    if (*start == '\0' || ft_strchr(start, '"') == NULL)
    {
        return merge_quotes(start - 1, '"'); // Pass opening quote
    }

    while (**saveptr && **saveptr != '"')
        (*saveptr)++;

    if (**saveptr == '"')
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    else
    {
        printf("Error: Unclosed double quote.\n");
        return (NULL);
    }
    return (start);
}

