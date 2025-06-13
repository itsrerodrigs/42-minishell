/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:54:30 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 17:16:27 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static t_builtin	*get_builtins(void)
{
	static t_builtin	builtins[] = {
	{"cd", builtin_cd},
	{"echo", builtin_echo},
	{"env", builtin_env},
	{"exit", builtin_exit},
	{"unset", builtin_unset},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{NULL, NULL}
	};

	return (builtins);
}

builtin_func	find_builtin(char *cmd)
{
	t_builtin	*builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(cmd, builtins[i].name, ft_strlen
				(builtins[i].name)) == 0 && ft_strlen(cmd)
			== ft_strlen(builtins[i].name))
		{
			return (builtins[i].func);
		}
			i++;
	}
	return (NULL);
}
