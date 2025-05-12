/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:24 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:46:52 by mmariano         ###   ########.fr       */
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
        printf("Error: Unmatched quote!\n");
        return (NULL);
    }

    *end = '\0';
    *saveptr = end + 1;
    return (start);
}

