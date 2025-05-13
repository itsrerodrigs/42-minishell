/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 21:17:49 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
 ** @brief: Sets up signal handling for SIGINT.
 */
static void setup_signal_handling(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed");
		exit(EXIT_FAILURE);
	}
}

/*
 ** @brief: Cleans up allocated memory for input.
 ** @param input: Pointer to the input token.
 */
void cleanup_input(t_token *input)
{
    if (!input)
        return;

    if (input->value)
        free(input->value);
    free(input);
}

/*
 ** @brief: Reads and processes user input.
 ** @return: Pointer to the next input token.
 */
static t_token *process_input(void)
{
    t_token *input = read_input();
    t_token **tokens;

    while (input != NULL)
    {
        if (!input->value)
        {
            free(input);
            input = read_input();
            continue;
        }

        tokens = get_tokens(input);
        if (tokens)
        {
            //ft_exec(tokens);
            free_tokens(tokens);
        }

        cleanup_input(input);
        input = read_input();
    }
    return (input);
}

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
