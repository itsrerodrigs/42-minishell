/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:23:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 14:48:05 by marieli          ###   ########.fr       */
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

/**
 * @brief Scans a command's arguments just before execution, replacing any
 * exit status markers with the current exit status.
 * @param cmd The command whose args will be scanned.
 * @param shell The shell struct containing the current exit status.
 */
void	late_expand_exit_status(t_command *cmd, t_shell *shell)
{
	int		i;
	char	*exit_str;
	char	*arg;
	char	*marker_pos;

	if (!cmd || !cmd->args)
		return ;
	exit_str = ft_itoa(shell->exit_status);
	if (!exit_str)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		marker_pos = ft_strnstr(arg, EXIT_STATUS_MARKER, ft_strlen(arg));
		if (marker_pos)
		{
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup(exit_str);
		}
		i++;
	}
	free(exit_str);
}