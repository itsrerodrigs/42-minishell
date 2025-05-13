/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 21:56:37 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* ---------------------------main do minishell!----------------------*/ 

int	main(int argc, char **argv)
{
	char	*line;
	char	**args;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	printbanner();
	line = read_input();
	while (line != NULL)
	{
		args = get_tokens(line);
		if (args)
		{
			ft_exec(args);
			free_tokens(args);
		}
		free(line);
		line = read_input();
	}
	return (EXIT_SUCCESS);
}

/*-----------------------------------------------------------------------------*/
/* main para testar tokenizaçao */

/* int main(void)
{
    char    *line;
    char    **args;
    int     i;

 */
