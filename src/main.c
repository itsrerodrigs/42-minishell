<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/09 16:23:03 by mmariano         ###   ########.fr       */
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:28 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:58:59 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	char	**args;
	t_shell	shell; 

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
			shell.current_cmd = malloc(sizeof(t_cmd));
			if (!shell.current_cmd)
				return (1); 
			shell.current_cmd->args = args;

			ft_exec(&shell);

			free(shell.current_cmd); // libera só o struct, args estao abaixo
			free_tokens(args);
		}
		free(line);
		line = read_input();
	}
	return (EXIT_SUCCESS);
}


/* ---------------------------main do minishell!----------------------*/ 
/*
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
    */

/*-----------------------------------------------------------------------------*/
/* main para testar tokenizaçao */

/* int main(void)
{
    char    *line;
    char    **args;
    int     i;

    printf("Waiting for input...\n");
    line = read_input();
    if (!line)
    {
        printf("read_input() returned NULL\n");
        return (1);
    }

    while (line != NULL)
    {
        printf("Line received: %s\n", line);
        args = get_tokens(line);
        if (!args)
        {
            printf("get_tokens() returned NULL\n");
            break;
        }

        i = 0;
        while (args[i] != NULL)
        {
            printf("Arg[%d]: %s\n", i, args[i]);
            i++;
        }
        if (args)
            free_tokens(args);
        line = read_input();
	}
    return (EXIT_SUCCESS);
} */
>>>>>>> builtins-test
