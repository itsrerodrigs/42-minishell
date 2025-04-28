/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:24 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/28 19:10:56 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char *append_until_quote(char *merged, char quote, char **saveptr)
{
    size_t dest_size = ft_strlen(merged) + 1;
    char *next;

    while (merged[ft_strlen(merged) - 1] != quote) // Check for closing quote
    {
        next = ft_strtok(NULL, DELIM, saveptr); // Fetch the next token
        if (!next) // If no closing quote is found
        {
            p(RED "Error: Unclosed quote detected in append_until_quote\n" RST);
            free(merged); // Clean up memory to prevent a leak
            return NULL;
        }

        // Expand the buffer to hold the next token plus a space
        dest_size += ft_strlen(next) + 2;
        char *temp = realloc(merged, dest_size);
        if (!temp) // If realloc fails
        {
            p(RED "Error: Memory reallocation failed in append_until_quote\n" RST);
            free(merged); // Clean up to prevent leaks
            return NULL;
        }
        merged = temp;

        ft_strlcat(merged, " ", dest_size); // Append a space
        ft_strlcat(merged, next, dest_size); // Append the next token
    }

    return merged; // Return the fully merged string
}

char *handle_quotes(char **saveptr, char quote)
{
    char *start;
    char *merged;
    size_t dest_size;

    start = ++(*saveptr); // Skip the opening quote
    dest_size = ft_strlen(start) + 1;

    merged = ft_malloc(dest_size); // Allocate memory for merged content
    if (!merged)
    {
        p(RED "Error: Memory allocation failed in handle_quotes\n" RST);
        return NULL;
    }
    ft_strlcpy(merged, start, dest_size); // Copy the content after the opening quote

    // Append the rest of the quoted content
    merged = append_until_quote(merged, quote, saveptr);
    if (!merged)
    {
        p(RED "Error: Unclosed quote detected in handle_quotes\n" RST);
        return NULL;
    }

    // Remove the closing quote
    merged[ft_strlen(merged) - 1] = '\0'; // Null-terminate after removing the closing quote
    return merged; // Return the cleaned-up token
}
