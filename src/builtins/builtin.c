/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/28 16:34:50 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * brief prints all the environment variables to the standart output
 * params args - an array of strings representing command-line arguments
 * return 0 on success or 1 if the environment variablws are not accessible
*/


int	ft_env(char **args)
{
	extern char	**environ;
	int	i;

	i = 0;
	(void)args;
	if (!environ)
		return(1);
	while (environ[i])
	{
		p("%s\n", environ[i]);
		i++;
	}
	return(0);
}
