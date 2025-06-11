/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:48:50 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 10:23:20 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token_with_fd(char *value, t_token_type type, int fd_val)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
    {
        free(value);
        return (NULL);
    }
    new_token->value = ft_strdup(value);
    if (!new_token->value) {
        free(new_token);
        free(value);
        return (NULL);
    }
    new_token->type = type;
    new_token->fd = fd_val;
    new_token->next = NULL;

    free(value);
    return (new_token);
}
