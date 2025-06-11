/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:23:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:12:35 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Gets the value of an environment variable from envp.
 * @param envp The environment array.
 * @param name The variable name (e.g. "PATH").
 * @return A pointer to the value, or NULL if not found.
 */
char *getenv_from_envp(char **envp, const char *name)
{
    size_t len;
    int i;

    len = ft_strlen(name);
    i = 0;
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (&envp[i][len + 1]);
        i++;
    }
    return (NULL);
}

/*
 * @brief Joins a directory and command into a full path.
 * @param dir Directory string (e.g., "/bin").
 * @param cmd Command name (e.g., "ls").
 * @return Malloc'd full path (e.g., "/bin/ls").
 */
char *join_path(const char *dir, const char *cmd)
{
    int len;
    char *full_path;

    len = ft_strlen(dir) + ft_strlen(cmd) + 2;
    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    ft_strlcpy(full_path, dir, len);
    ft_strlcat(full_path, "/", len);
    ft_strlcat(full_path, cmd, len);
    return (full_path);
}

/*
 * @brief Frees a NULL-terminated array of strings.
 * @param arr The string array to free.
 */
void free_split(char **arr)
{
    int i;

    i = 0;
    while (arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}