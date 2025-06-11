/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:55:56 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:23:15 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* @brief duplicates the environment array
*/
char	**dup_envp(char **envp)
{
	int	count;
	int	index;
	char	**new_env;

	count = 0;
	index = 0;
	while (envp[count])
		count++;
	new_env = calloc(count + 1, sizeof(char *));
	if (!new_env)
		return NULL;
	while (envp[index])
	{
		new_env[index] = strdup(envp[index]);
		if (!new_env[index])
		{
			while (index > 0)
				free(new_env[--index]);
			free(new_env);
			return NULL;
		}
		index++;
	}
	return new_env;
}

/*
 * @brief frees the duplicated environment
 */
void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

/*
* @brief prints all environment variables
* @params shell shows structure containing the current envp
* @note should only print variables that has a value (i.e. in KEY=VALUE format)
*/

int	builtin_env(t_shell *shell, char **args)
{
	int	i;

	(void)args;
	if (!shell || !shell->envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
