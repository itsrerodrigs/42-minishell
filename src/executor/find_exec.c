/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 20:57:59 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/31 20:57:59 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <unistd.h>
#include <stdlib.h>

/*
 * @brief Locates the full path of a given command using PATH.
 * @param cmd The command name (e.g., "ls").
 * @param shell Shell context containing envp.
 * @return A malloc'd string with the path, or NULL if not found.
 */
char *find_executable(char *cmd, t_shell *shell)
{
    char **paths;
    char *full_path;
    char *path_env;
    int i;

    if (!cmd || ft_strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0) {
            return (ft_strdup(cmd));
        } else {
            return (NULL);
        }
    }

    path_env = getenv_from_envp(shell->envp, "PATH");
    if (!path_env)
        return (NULL);

    paths = ft_split(path_env, ':');
    if (!paths) {
        return (NULL);
    }

    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
        {
            return (free_split(paths), full_path);
        }
        free(full_path);
        i++;
    }

    free_split(paths);
    return (NULL);
}