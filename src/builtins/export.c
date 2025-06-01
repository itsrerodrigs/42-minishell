/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:56:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:14:53 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

/*
* @brief adds or updates environment variables in the shell
* @params shell shows context structure that contains envp & accept args in format KEY=VALUE and only KEY
* @note if called with no args, it should print the environment in a shorted format
* if an args has no "=", it adds an empty variable name with no value
* invalid identifiers must be handled and produce an error but not crash (i.e. starting w/ a digit or containing !, - or others)
*/

static void	sort_env(char **envp)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		j = i + 1;
		while (envp[j])
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i]) + 1) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static int	ft_try_update_existing_var(char **envp, const char *var,
										size_t key_len, int var_has_value, int i)
{
	if (ft_strncmp(envp[i], var, key_len) == 0)
	{
		if (var_has_value && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			if (!envp[i])
				ft_handle_error("strdup");
			return (1);
		}
		else if (!var_has_value && envp[i][key_len] == '\0')
			return (1);
		else if (!var_has_value && envp[i][key_len] == '=')
			return (1);
	}
	return (0);
}

static void	add_or_update_env(char ***envp, const char *var)
{
	int		i;
	char	*equals_pos;
	size_t	key_len;
	int		var_has_value;

	i = 0;
	equals_pos = ft_strchr(var, '=');
	var_has_value = (equals_pos != NULL);
	if (var_has_value)
		key_len = equals_pos - var;
	else
		key_len = ft_strlen(var);
	while ((*envp)[i])
	{
		if (ft_try_update_existing_var(*envp, var, key_len, var_has_value, i))
			return ;
		i++;
	}
	*envp = (char **)ft_realloc(*envp, sizeof(char *) * (i + 2)); // CORRIGIDO AQUI!
	if (!(*envp))
		ft_handle_error("realloc");
	(*envp)[i] = ft_strdup(var);
	if (!(*envp)[i])
		ft_handle_error("strdup");
	(*envp)[i + 1] = NULL;
}

int	builtin_export(t_shell *shell, char **args)
{
	int	i;

	if (!shell || !shell->envp)
		return (1);
	if (!args[1])
	{
		sort_env(shell->envp);
		i = 0;
		while (shell->envp[i])
		{
			ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
			i++;
		}
		return (0);
	}
	i = 1;
	while (args[i])
	{
		add_or_update_env(&shell->envp, args[i]);
		i++;
	}
	return (0);
}