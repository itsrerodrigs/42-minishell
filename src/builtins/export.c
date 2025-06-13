/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:56:49 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 19:43:31 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	sort_env_array(char **envp, int len)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
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

static void	print_exported_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("declare -x %s\n", envp[i]);
		i++;
	}
}

/* @brief Sorts and prints all environment variables for 'export' with no args.
 */
static void	print_sorted_env_for_export(char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	sort_env_array(envp, len);
	print_exported_env(envp);
}

/* @brief Adds or updates an environment variable in the shell's environment.
 * @param envp_ptr Pointer to the shell's environment array (char ***).
 * @param var The variable string (e.g., "KEY=VALUE" or "KEY").
 * @return 0 on success, 1 on failure (e.g., memory allocation, invalid name).
 */
int	add_or_update_env(char ***envp_ptr, const char *var)
{
	char	*equals_pos;
	int		var_has_value;
	int		i;
	size_t	key_len;

	i = 0;
	equals_pos = ft_strchr(var, '=');
	var_has_value = (equals_pos != NULL);
	if (var_has_value)
		key_len = equals_pos - var;
	else
		key_len = ft_strlen(var);
	if (!is_valid_env_name(var, key_len))
		return (1);
	while ((*envp_ptr)[i])
	{
		if (try_update_existing_var(envp_ptr, var, key_len, var_has_value))
			return (0);
		i++;
	}
	if (!add_new_env_entry(envp_ptr, var, i))
		return (1);
	return (0);
}

/* @brief Adds variables to the environment or prints all environment variables.
 */
int	builtin_export(t_shell *shell, char **args)
{
	int	i;
	int	return_status;

	return_status = 0;
	if (!shell || !shell->envp)
		return (1);
	if (!args[1])
		print_sorted_env_for_export(shell->envp);
	else
	{
		i = 1;
		while (args[i])
		{
			if (add_or_update_env(&shell->envp, args[i]) != 0)
			{
				ft_putstr_fd("minishell: export: `", STDERR_FILENO);
				ft_putstr_fd(args[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
				return_status = 1;
			}
			i++;
		}
	}
	return (return_status);
}
