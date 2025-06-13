/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:22:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 21:43:51 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* @brief updates the OLDPWD and PWD environment variables.
*/
void	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];
	char	*oldpwd_var;
	char	*pwd_var;

	oldpwd_var = ft_strjoin(ft_strdup("OLDPWD="), oldpwd);
	add_or_update_env(&shell->envp, oldpwd_var);
	free(oldpwd_var);
	if (getcwd(cwd, sizeof(cwd)))
	{
		pwd_var = ft_strjoin(ft_strdup("PWD="), cwd);
		add_or_update_env(&shell->envp, pwd_var);
		free(pwd_var);
	}
}

/*
* @brief prints the current working directory
* @params shows shell context structure & ignored args if not informed
* @note doesn't change the current directory, only displays the path
*/

int	builtin_pwd(t_shell *shell, char **args)
{
	char	cwd[PATH_MAX];

	(void)shell;
	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}
