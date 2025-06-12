/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:15:11 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 11:01:52 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "builtins.h"

/**
 * @brief Checks if an environment variable's key matches any of the arguments
 * provided to the unset command.
 * @param env_var The environment variable string (e.g., "USER=marieli").
 * @param args_to_unset The arguments array from the unset command, starting
 * with "unset".
 * @return 1 if a match is found (should be unset), 0 otherwise.
 */
static int	should_be_unset(const char *env_var, char **args_to_unset)
{
	size_t	key_len;
	int		i;

	key_len = 0;
	while (env_var[key_len] && env_var[key_len] != '=')
		key_len++;
	i = 1;
	while (args_to_unset[i])
	{
		if (ft_strlen(args_to_unset[i]) == key_len
			&& ft_strncmp(env_var, args_to_unset[i], key_len) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief Removes one or more environment variables in an efficient,
 * single-pass operation.
 */
int	builtin_unset(t_shell *shell, char **args)
{
	int	read_idx;
	int	write_idx;

	if (!shell || !shell->envp || !args[1])
		return (0);
	read_idx = 0;
	write_idx = 0;
	while (shell->envp[read_idx])
	{
		if (should_be_unset(shell->envp[read_idx], args))
			free(shell->envp[read_idx]);
		else
		{
			shell->envp[write_idx] = shell->envp[read_idx];
			write_idx++;
		}
		read_idx++;
	}
	shell->envp[write_idx] = NULL;
	return (0);
}
