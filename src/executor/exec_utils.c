/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:23:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 12:23:49 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/*
 * @brief Retrieves the value of an environment variable.
 * @param envp Environment variable array (NULL-terminated).
 * @param name The variable name to look for.
 * @return Pointer to the variable value or NULL if not found.
 */
char *getenv_from_envp(char **envp, const char *name)
{
    int i;
    size_t len;


    i = 0;
    len = ft_strlen(name);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return (NULL);
}

/*
 * @brief Concatenates a directory and a command with a slash.
 * @param s1 Directory (e.g., "/bin")
 * @param s2 Command (e.g., "ls")
 * @return Newly allocated string "s1/s2".
 */
char *ft_strjoin_path(char *s1, char *s2)
{
    char   *joined;
    size_t  len1;
    size_t  len2;
    int     i;


    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    joined = malloc(len1 + len2 + 2);
    if (!joined)
        return (NULL);
    i = -1;
    while (++i < (int)len1)
        joined[i] = s1[i];
    joined[i++] = '/';
    while (*s2)
        joined[i++] = *s2++;
    joined[i] = '\0';
    return (joined);
}

/*
 * @brief Frees a NULL-terminated array of strings.
 * @param arr Array to free.
 */
void free_split(char **arr)
{
    int i;


    if (!arr)
        return ;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

/*
* @brief resolves the full path of a command usint the path variable
* @param cmd the command name (like ls)
* envp the environment array to extract PATH from
* @return the full path to the executable if found, otherwise NULL
* @note if the command already contains a '/', it is tested directly
* the return must be
*/
char	*find_executable(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*result;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = getenv_from_envp(envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	result = get_cmd_path(cmd, paths);
	free_split(paths);
	return (result);
}

/*
* @brief searches for the command in an array of path directories
* @param cmd the name of the command to search for
* paths the array of directories to search in (split path)
* @return a new allocated string with the full path to the command or NULL if not found
* @note the returned string must be freed by the caller
*/
char    *get_cmd_path(char *cmd, char **paths)
{
    char    *path;
    int     i;

    i = 0;
    while (paths[i])
    {
        path = ft_strjoin_path(paths[i], cmd);
        if (!path)
        {
            i++;
            continue ;
        }
        if (access(path, X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    return (NULL);
}