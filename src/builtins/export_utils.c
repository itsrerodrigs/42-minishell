/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:52:47 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/10 14:54:09 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Checks if an environment variable name is valid.
 * This function is now public (not static).
 * @param name The variable name string.
 * @param name_len The length of the name part (before '=' if present).
 * @return 1 if valid, 0 otherwise.
 */
int	is_valid_env_name(const char *name, size_t name_len)
{
	size_t	i;

	i = 0;
	if (name_len == 0 || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i++;
	while (i < name_len)
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * @brief Attempts to update an existing environment variable.
 * This function is now public (not static).
 * @param envp_ptr Pointer to the shell's environment array.
 * @param var The variable string to add/update.
 * @param key_len Length of the variable name.
 * @param var_has_value Flag indicating if 'var' includes a value (e.g., KEY=VALUE).
 * @return 1 if variable was found and updated/kept, 0 otherwise.
 */
int	try_update_existing_var(char ***envp_ptr, const char *var,
		size_t key_len, int var_has_value)
{
	int	i;

	i = 0;
	char *existing_entry;
	while ((*envp_ptr)[i])
	{
		existing_entry = (*envp_ptr)[i];
		if (ft_strncmp(existing_entry, var, key_len) == 0 &&
				(existing_entry[key_len] == '=' 
				 || existing_entry[key_len] == '\0'))
		{
			if (var_has_value && existing_entry[key_len] == '=')
			{
				free(existing_entry);
				(*envp_ptr)[i] = ft_strdup(var);
				if (!(*envp_ptr)[i])
				{
					perror("minishell: strdup failed in export update");
					exit(EXIT_FAILURE);
				}
			}
			return (1);
		}
		i++;
	}
	return (0);
}


