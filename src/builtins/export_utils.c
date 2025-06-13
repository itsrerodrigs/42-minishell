/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:52:47 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 19:16:14 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

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


int	try_update_existing_var(char ***envp, const char *var,
				size_t len, int has_val)
{
	int		i;
	char	*entry;

	i = 0;
	while ((*envp)[i])
	{
		entry = (*envp)[i];
		if (ft_strncmp(entry, var, len) == 0
			&& (entry[len] == '=' || entry[len] == '\0'))
		{
			if (has_val && entry[len] == '=')
			{
				free(entry);
				(*envp)[i] = ft_strdup(var);
				if (!(*envp)[i])
					perror("minishell: strdup failed in export");
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	add_new_env_entry(char ***envp_ptr, const char *var, int i)
{
	char	**new_envp_array;

	new_envp_array = (char **)ft_realloc(*envp_ptr, sizeof(char *) * (i + 2));
	if (!new_envp_array)
	{
		perror("minishell: realloc failed in export");
		return (0);
	}
	*envp_ptr = new_envp_array;
	(*envp_ptr)[i] = ft_strdup(var);
	if (!(*envp_ptr)[i])
	{
		perror("minishell: strdup failed in export");
		return (0);
	}
	(*envp_ptr)[i + 1] = NULL;
	return (1);
}
