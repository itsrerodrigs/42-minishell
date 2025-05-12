/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:16:28 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

static void remove_env_var(char ***envp, const char *key)
{
    int i = 0, j = 0;
    char **new_envp;

    while ((*envp)[i])
        i++;
    new_envp = ft_malloc(sizeof(char *) * i); // Aloca espaço para o novo envp
    i = 0;
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0 &&
            (*envp)[i][ft_strlen(key)] == '=')
            free((*envp)[i]);
        else
            new_envp[j++] = (*envp)[i];
        i++;
    }
    new_envp[j] = NULL;
    free(*envp);
    *envp = new_envp;
}

int builtin_unset(t_shell *shell, char **args)
{
    int i = 1;

    if (!shell || !shell->envp)
        return (1);
    while (args[i])
        remove_env_var(&shell->envp, args[i++]);
    return (0);
}