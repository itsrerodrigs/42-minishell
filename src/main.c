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
#include <readline/readline.h>
#include <readline/history.h>

/*
 * @brief Initializes the shell struct.
 * @param shell The shell structure to fill.
 * @param envp The environment variables.
 */
void init_shell(t_shell *shell, char **envp)
{
    shell->envp = dup_envp(envp);
    shell->exit_status = 0;
    shell->current_cmd = NULL;
}

/*
 * @brief Frees everything for a new input cycle.
 */
void cleanup_cycle(t_shell *shell, char *input, t_token *tokens)
{
    if (input)
        free(input);
    if (shell->current_cmd)
    {
        free_commands(shell->current_cmd);
        shell->current_cmd = NULL;
    }
    if (tokens)
        free_tokens(tokens);
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    char *input;
    t_token *tokens;

    (void)argc;
    (void)argv;
    init_shell(&shell, envp);
    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
            break;
        if (*input)
            add_history(input);
        tokens = get_tokens(input, &shell);
        if (!tokens)
        {
            cleanup_cycle(&shell, input, NULL);
            continue;
        }
        shell.current_cmd = parse_tokens(tokens, &shell);
        if (shell.current_cmd)
            ft_exec(&shell);
        cleanup_cycle(&shell, input, tokens);
    }
    free_envp(shell.envp);
    return (0);
}
