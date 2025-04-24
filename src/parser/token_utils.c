/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:12 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/24 18:29:15 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void free_tokens(char **tokens)
{
    unsigned int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}

