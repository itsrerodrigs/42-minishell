/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/06 15:13:18 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* current directory 
* @brief changes the current working directory of the shell process
* @param shell shows shell in the context structure
* @param args arguments in the second index args[1] is the target path
* @note if doesn't have any arguments, it should change to $HOME directory
*/

// int	builtin_cd(t_shell *shell, char **args)
// {
// 	char	*path;
// 	char	cwd[PATH_MAX];
// 	char	*oldpwd;

// 	path = get_cd_path(shell, args);
// 	if (!path)
// 		return (1);
// 	if (!getcwd(cwd, sizeof(cwd)))
// 		return (1);
// 	oldpwd = ft_strdup(cwd);
// 	if (!oldpwd)
// 		return (1);
// 	if (chdir(path) != 0)
// 	{
// 		ft_putstr_fd("cd: ", STDERR_FILENO);
// 		perror(path);
// 		free(oldpwd);
// 		return (1);
// 	}
// 	update_pwd_vars(shell, oldpwd);
// 	free(oldpwd);
// 	return (0);
// }

int	builtin_cd(t_shell *shell, char **args)
{
	char	*path_to_go;
	char	*old_pwd_val;
	int		status;

	path_to_go = get_cd_path_expanded(shell, args);
	if (!path_to_go)
		return (1);
	old_pwd_val = save_and_get_oldpwd();
	if (!old_pwd_val)
		return (1);
	status = execute_chdir(path_to_go);
	if (status != 0)
	{
		free(old_pwd_val);
		return (1);
	}
	update_pwd_vars(shell, old_pwd_val);
	free(old_pwd_val);
	return (0);
}