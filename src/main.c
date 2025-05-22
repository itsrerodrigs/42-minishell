/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parsing.h"


int main(void)
{
	t_token *input;
	
    setup_signal_handling();
    p(C "Initializing Minishell.. \n" RST);
	while(1)
	{
		input = process_input();
		if (!input) 
			break;
	}		
    return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/* main para testa os tokens*/

/* int main(void)
{
    t_token *input;
    t_token **tokens;
    
    while (1)
    {
        input = read_input();
        if (!input)
            break;
        tokens = get_tokens(input);
        if (tokens)
        {
            int i = 0;
            while (tokens[i])
            {
                printf("%s\n", tokens[i]->value);
                i++;
            }
            free_tokens(tokens);
        }
        else
        {
            printf("no tokens found");
        }
        cleanup_input(input); 
    }
    return (EXIT_SUCCESS);
}

 */
