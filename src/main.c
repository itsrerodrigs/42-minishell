/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/28 17:06:44 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int main(int argc, char **argv)
{
	char			*line;
	char 			**args;

	(void)argc;
    (void)argv;

	signal(SIGINT, sigint_handler); //para Ctrl+C
	printbanner();
	
	line = read_input(); //lê o input com o readline()
	while (line != NULL) //começa o REPL loop
	{
		p(G "Looping through REPL...\n" RST); // Debug message
		args = get_tokens(line); //aqui é onde acontece a tokenização
		if (args)
		{
			ft_exec(args); //esa função vai lidar com a execução dos comandos
            free_tokens(args); //free tokens
		}
		free(line);
		line = read_input();		
	}
	return (EXIT_SUCCESS);
}
