/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:22:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/10 14:49:49 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
