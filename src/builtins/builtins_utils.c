/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:23:01 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 13:37:25 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
* @brief get the path to change the directory to
* @note returns HOME if no arguments is given
*/
char	*get_cd_path(t_shell *shell, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = get_env_value(shell->envp, "HOME");
		if (!path)
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
	}
	else
		path = args[1];
	return (path);
}

/* 
* @brief updates the OLDPWD and PWD environment variables.
*/
void	update_pwd_vars(t_shell *shell, char *oldpwd)
{
	char	cwd[PATH_MAX];

	update_env_var(shell, "OLDPWD", oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var(shell, "PWD", cwd);
}

/*
 * @brief updates or adds an environment variable.
 */
void	update_env_var(t_shell *shell, const char *key, const char *value)
{
	char	*new_var;
	char	*equal_sign;
	size_t	new_size;
	size_t	i;

	new_size = ft_strlen(key) + ft_strlen(value) + 2;
	i = 0;
	new_var = malloc(new_size);
	if (!new_var)
		return;
	ft_strlcpy(new_var, key, new_size);
	ft_strlcat(new_var, "=", new_size);
	ft_strlcat(new_var, value, new_size);
	while (shell->envp[i])
	{
		equal_sign = ft_strchr(shell->envp[i], '=');
		if (equal_sign && ft_strncmp(shell->envp[i], key, equal_sign - shell->envp[i]) == 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = new_var;
			return;
		}
		i++;
	}
	//mari: troquei realloc_mem por ft_realloc por causa do leak de memória
	// shell->envp = realloc_mem(shell->envp, (i + 2) * sizeof(char *));
	shell->envp = ft_realloc(shell->envp, (i + 2) * sizeof(char *));
	if (shell->envp)
	{
		shell->envp[i] = new_var;
		shell->envp[i + 1] = NULL;
	}
}

/*
 * @brief checks if a string contains only digits.
 */
int	ft_isdigit_str(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			return (0);
		}
		str++;
	}
	return (1);
}
