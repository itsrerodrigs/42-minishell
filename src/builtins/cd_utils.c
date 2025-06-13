/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:53:25 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 17:16:36 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static char	*get_home_path(t_shell *shell)
{
	char	*home_val;

	home_val = get_env_value(shell->envp, "HOME");
	if (!home_val)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (NULL);
	}
	return (ft_strdup(home_val));
}


static char	*get_oldpwd_path(t_shell *shell)
{
	char	*oldpwd_val;

	oldpwd_val = get_env_value(shell->envp, "OLDPWD");
	if (!oldpwd_val)
	{
		ft_putendl_fd("cd: OLDPWD not set", STDERR_FILENO);
		return (NULL);
	}
	ft_putendl_fd(oldpwd_val, STDOUT_FILENO);
	return (ft_strdup(oldpwd_val));
}

char	*get_cd_path(t_shell *shell, char **args)
{
	if (!args[1])
		return (get_home_path(shell));
	else if (ft_strcmp(args[1], "-") == 0)
		return (get_oldpwd_path(shell));
	else
		return (ft_strdup(args[1]));
}
