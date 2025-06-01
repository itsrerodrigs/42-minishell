/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:16:28 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdlib.h>

static void	ft_handle_error(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void	ft_free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static int	ft_count_vars_to_keep(char **envp, const char *key)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (!(ft_strncmp(envp[i], key, ft_strlen(key)) == 0 && \
			envp[i][ft_strlen(key)] == '='))
			count++;
		i++;
	}
	return (count);
}

static int	ft_copy_and_check_var(char **new_envp, int j, const char *str)
{
	new_envp[j] = ft_strdup(str);
	if (!new_envp[j])
	{
		ft_free_str_array(new_envp);
		ft_handle_error("strdup");
		return (0);
	}
	return (1);
}

static void	remove_env_var(char ***envp_ptr, const char *key)
{
	char	**old_envp;
	char	**new_envp;
	int		i;
	int		j;
	int		count;

	old_envp = *envp_ptr;
	i = 0;
	j = 0;
	count = ft_count_vars_to_keep(old_envp, key);
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		ft_handle_error("malloc");
	while (old_envp[i])
	{
		if (!(ft_strncmp(old_envp[i], key, ft_strlen(key)) == 0 && \
			old_envp[i][ft_strlen(key)] == '='))
		{
			if (!ft_copy_and_check_var(new_envp, j, old_envp[i]))
				return ;
			j++;
		}
		free(old_envp[i]);
		i++;
	}
	new_envp[j] = NULL;
	free(old_envp);
	*envp_ptr = new_envp;
}

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	if (!shell || !shell->envp)
		return (1);
	i = 1;
	while (args[i])
	{
		remove_env_var(&shell->envp, args[i]);
		i++;
	}
	return (0);
}