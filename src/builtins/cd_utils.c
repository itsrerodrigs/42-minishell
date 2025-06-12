/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:53:25 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 12:09:32 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gets the path to HOME for 'cd' or 'cd ~'.
 */
static char *get_home_path(t_shell *shell)
{
    char *home_val = get_env_value(shell->envp, "HOME");
    if (!home_val)
    {
        ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
        return (NULL);
    }
    return (ft_strdup(home_val));
}

/**
 * @brief function to handle 'cd -'.
 */
static char *get_oldpwd_path(t_shell *shell)
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

/**
 * @brief Determines the target path for the 'cd' command based on arguments,
 * using helper functions for special cases.
 * NOTE: Tilde expansion (e.g., `~/Documents`) is now handled by the main parser
 * before this function is called.
 */
char	*get_cd_path(t_shell *shell, char **args)
{
	if (!args[1])
		return (get_home_path(shell));
	else if (ft_strcmp(args[1], "-") == 0)
		return (get_oldpwd_path(shell));
	else
		return (ft_strdup(args[1]));
}
