/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 17:16:40 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static int	cd_error(char *path, char *oldpwd, const char *perror_arg)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	perror(perror_arg);
	if (path)
		free(path);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	path = get_cd_path(shell, args);
	if (!path)
		return (1);
	oldpwd = NULL;
	if (!getcwd(cwd, sizeof(cwd)))
		return (cd_error(path, NULL, "getcwd"));
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (cd_error(path, NULL, "strdup"));
	if (chdir(path) != 0)
		return (cd_error(path, oldpwd, path));
	update_pwd_vars(shell, oldpwd);
	free(oldpwd);
	free(path);
	return (0);
}
