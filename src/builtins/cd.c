/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 17:42:44 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles errors for the 'cd' builtin by printing a standard error
 * message with perror, freeing any allocated memory, and returning 1.
 * @param path The path string to free, if allocated.
 * @param oldpwd The oldpwd string to free, if allocated.
 * @param perror_arg The string to pass to perror() to identify the error source.
 * @return Always returns 1 to indicate failure.
 */
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


/* current directory 
* @brief changes the current working directory of the shell process
* @param shell shows shell in the context structure
* @param args arguments in the second index args[1] is the target path
* @note if doesn't have any arguments, it should change to $HOME directory
*/
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
