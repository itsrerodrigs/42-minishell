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
#include "../inc/parser.h"


/*int main(void)
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
*/
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
#include "../inc/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ARGS 100

char **simple_split(char *input)
{
    char **args = malloc(sizeof(char *) * (MAX_ARGS + 1));
    char *token;
    int i = 0;

    if (!args)
        return NULL;

    token = strtok(input, " \t\n");
    while (token && i < MAX_ARGS)
    {
        args[i++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
    return args;
}

void fill_shell_struct(t_shell *shell, char **args)
{
    shell->current_cmd = malloc(sizeof(t_command));
    if (!shell->current_cmd)
        return;
    shell->current_cmd->args = args;
}

int main(void)
{
    char *input;
    char **args;
    t_shell shell;

    while (1)
    {
        input = readline("minishell-test$ ");
        if (!input)
            break;
        if (input[0] != '\0')
            add_history(input);

        args = simple_split(input);
        if (!args || !args[0])
        {
            free(input);
            continue;
        }

        fill_shell_struct(&shell, args);

        if (exec_builtin(&shell) == 0)
            printf("Not a builtin: %s\n", args[0]);

        // limpar
        for (int i = 0; args[i]; i++)
            free(args[i]);
        free(args);
        free(shell.current_cmd);
        free(input);
    }

    return 0;
}
