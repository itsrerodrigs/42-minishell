/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 16:02:39 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* unset.c                                            :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*<y_bin_115>   +#+           */
/* Created: 2025/05/02 17:15:11 by renrodri          #+#    #+#             */
/* Updated: 2025/06/11 16:00:00 by marieli          ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Copies variables to a new env array, skipping the one to be unset.
 */
static char	**build_new_env(char **old, char **new_env, const char *key)
{
	int	i;
	int	j;
	int	key_len;

	i = 0;
	j = 0;
	key_len = ft_strlen(key);
	while (old[i])
	{
		if (!(ft_strncmp(old[i], key, key_len) == 0 && old[i][key_len] == '='))
		{
			new_env[j] = ft_strdup(old[i]);
			if (!new_env[j])
			{
				free_envp(new_env);
				perror("strdup");
				return (NULL);
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

/**
 * @brief Removes an environment variable.
 */
static void	remove_env_var(char ***envp_ptr, const char *key)
{
	char	**old_envp;
	char	**new_envp;
	int		count;
	int		i;

	old_envp = *envp_ptr;
	count = 0;
	i = 0;
	while (old_envp[i])
	{
		if (!(ft_strncmp(old_envp[i], key, ft_strlen(key)) == 0 && \
			old_envp[i][ft_strlen(key)] == '='))
			count++;
		i++;
	}
	new_envp = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!new_envp)
	{
		perror("malloc");
		return ;
	}
	new_envp = build_new_env(old_envp, new_envp, key);
	free_envp(old_envp);
	*envp_ptr = new_envp;
}

/**
 * @brief Removes one or more environment variables.
 */
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
