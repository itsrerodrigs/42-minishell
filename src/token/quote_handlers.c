/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:24 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/01 19:33:12 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


char *handle_quotes(char **saveptr, char quote_char)
{
    char *start, *end;

    if (!saveptr || !*saveptr || **saveptr != quote_char)
        return NULL;

    start = ++(*saveptr);
    end = start;

    while (*end && *end != quote_char)
        end++;

    if (*end == '\0')
    {
        printf("Debug: Unmatched quote detected\n");
        return NULL;
    }

    *end = '\0';
    *saveptr = end + 1;
    printf("Debug: Extracted quoted string -> %s\n", start);
    return start;
}

