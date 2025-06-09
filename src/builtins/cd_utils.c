/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:53:25 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 17:07:27 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief
*/
char    *get_cd_path_expanded(t_shell *shell, char **args)
{
	char	*path_str;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path_str = get_env_value(shell->envp, "HOME");
		if (!path_str)
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
    }
		else if (ft_strcmp(args[1], "-") == 0)
		{
			path_str = get_env_value(shell->envp, "OLDPWD");
			if (!path_str)
				ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
			else
				ft_putendl_fd(path_str, STDERR_FILENO);
		}
		else
		{
			path_str = args[1];
		}
		return (path_str);
}


/*
* @brief
*/
char    *save_and_get_oldpwd(void)
{
    char    cwd[PATH_MAX];
    char    *oldpwd_str;

    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("minishell: cd: getcwd (save_oldpwd)");
        return (NULL);
    }
    oldpwd_str = ft_strdup(cwd);
    if (!oldpwd_str)
        perror("minishell: cd: ft_strdup (oldpwd)");
    return (oldpwd_str);
}

/*
* @brief
*/

int     execute_chdir(const char *path)
{
    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", STDERR_FILENO);
        perror(path);
        return (1);
    }
    return (0);
}

// In file: 42-minishell/src/builtins/builtins_utils.c

// Auxiliary function to handle 'cd' or 'cd ~'
static char *s_get_home_path(t_shell *shell)
{
    char *home_val = get_env_value(shell->envp, "HOME");
    if (!home_val)
    {
        ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
        return (NULL);
    }
    return (ft_strdup(home_val));
}

// Auxiliary function to handle 'cd -'
static char *s_get_oldpwd_path(t_shell *shell)
{
    char *oldpwd_val = get_env_value(shell->envp, "OLDPWD");
    if (!oldpwd_val)
    {
        ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
        return (NULL);
    }
    ft_putendl_fd(oldpwd_val, STDOUT_FILENO);
    return (ft_strdup(oldpwd_val));
}

// Auxiliary function to handle 'cd ~/path'
static char *s_get_tilde_expanded_path(t_shell *shell, char *arg)
{
    char *home_val = get_env_value(shell->envp, "HOME");
    if (!home_val)
    {
        ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
        return (NULL);
    }
    char *path = ft_strjoin(ft_strdup(home_val), arg + 1);
    if (!path)
        perror("cd: malloc failed for path expansion");
    return (path);
}

// Refactored get_cd_path function
char *get_cd_path(t_shell *shell, char **args)
{
    if (!args[1] || ft_strcmp(args[1], "~") == 0)
        return (s_get_home_path(shell));
    else if (ft_strcmp(args[1], "-") == 0)
        return (s_get_oldpwd_path(shell));
    else if (ft_strncmp(args[1], "~/", 2) == 0)
        return (s_get_tilde_expanded_path(shell, args[1]));
    else
        return (ft_strdup(args[1])); // Direct path, duplicate for consistent freeing
}
