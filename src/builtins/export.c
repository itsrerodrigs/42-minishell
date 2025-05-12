/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:56:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:14:53 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

static void sort_env(char **envp)
{
    int i, j;
    char *temp;

    for (i = 0; envp[i]; i++)
    {
        for (j = i + 1; envp[j]; j++)
        {
            if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i]) + 1) > 0)
            {
                temp = envp[i];
                envp[i] = envp[j];
                envp[j] = temp;
            }
        }
    }
}

static void add_or_update_env(char ***envp, const char *var)
{
    int i = 0;
    size_t key_len = ft_strchr(var, '=') - var;

    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], var, key_len) == 0 && (*envp)[i][key_len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = ft_strdup(var);
            return;
        }
        i++;
    }
    *envp = ft_realloc(*envp, sizeof(char *) * (i + 2));
    (*envp)[i] = ft_strdup(var);
    (*envp)[i + 1] = NULL;
}

int builtin_export(t_shell *shell, char **args)
{
    int i = 1;

    if (!shell || !shell->envp)
        return (1);
    if (!args[1])
    {
        sort_env(shell->envp);
        for (i = 0; shell->envp[i]; i++)
            ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
        return (0);
    }
    while (args[i])
        add_or_update_env(&shell->envp, args[i++]);
    return (0);
}