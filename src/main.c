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

#include "minishell.h"
#include "tokens.h"
#include "parser.h"
#include "debug.h"
#include "sig.h"


int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    char *input;
    t_token *tokens;
    t_command *commands;

    (void)argc;
    (void)argv;

    /* Initialize shell structure */
    shell.envp = envp;
    shell.exit_status = 0;
    shell.current_cmd = NULL;

    /* Set up Ctrl+C signal handler */
    setup_signal_handling();
    p(C "Initializing Minishell..\n" RST);

   /* Main loop: read input, tokenize, parse, and execute */
    while (1)
    {
        input = read_input();
        if (!input)
            break;
        tokens = get_tokens(input, &shell);
        if (!tokens)
        {
            free(input);
            continue;
        }
        commands = parse_tokens(tokens, &shell);
        shell.current_cmd = commands;        
        ft_exec(&shell);
        free_tokens(tokens);
        free_commands(commands);
        free(input);
    }
    return (EXIT_SUCCESS);
}
