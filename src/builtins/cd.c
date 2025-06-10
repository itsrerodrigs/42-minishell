/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/10 14:50:17 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	(void)args;
	path = get_cd_path(shell, args);
	if (!path)
		return (1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		free(oldpwd);
		return (1);
	}
	update_pwd_vars(shell, oldpwd);
	free(oldpwd);
	return (0);
}
