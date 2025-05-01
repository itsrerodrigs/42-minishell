/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/01 17:09:05 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

/* main do minishell!
int main(int argc, char **argv)
{
	char			*line;
	char 			**args;

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
*/

/*-----------------------------------------------------------------------------*/
/* main para testar tokenizaçao */

int	main(void)
{
	char	*line;
	char	**args;
    int     i;

	line = read_input();
    if (!line)
		return(1);
	while (line != NULL)
    {
        args = get_tokens(line);
        {
            i = 0;
            while (args[i] != NULL)
            {
            printf("Arg[%d]: %s\n", i, args[i]);
            i++;
            }
        }
    }
	if(args)
    	free_tokens(args);
	return (EXIT_SUCCESS);
}