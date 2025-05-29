/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:29:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parsing.h"
#include "debug.h"

/*
 ** @brief: Constructs and returns the prompt string.
 ** @return: dynamically allocated prompt string 
 */
char *display_prompt(void)
{
    char cwd[BUFSIZ];
    char *prompt;
    size_t prompt_size;

    if (isatty(fileno(stdin)))
    {
        getcwd(cwd, sizeof(cwd));
        prompt_size = ft_strlen(G) + ft_strlen(cwd) + ft_strlen(" minishell> ") +
                      ft_strlen(RST) + 1;
        prompt = ft_malloc(prompt_size);
        if (!prompt)
            return (NULL);
        prompt[0] = '\0';
        ft_strlcat(prompt, G, prompt_size);
        ft_strlcat(prompt, cwd, prompt_size);
        ft_strlcat(prompt, " minishell> ", prompt_size);
        ft_strlcat(prompt, RST, prompt_size);
        return (prompt);
    }
    return (strdup("minishell> "));
}

/*
 ** @brief: Reads user input using the prompt and returns a token.
 ** @return: pointer to a token containing the user input
 */
char *read_input(void)
{
    char *buf;
    char *prompt;

    prompt = display_prompt();
    buf = readline(prompt);
    free(prompt);
    if (!buf)
    {
        p(RED "[EOF]: Exiting minishell.\n" RST);
        return (NULL);
    }
    if (*buf)
        add_history(buf);
    if (ft_strncmp(buf, "exit", 4) == 0 && ft_strlen(buf) == 4)
    {
        free(buf);
        exit(0);
    }
    return (buf);
}
/*
 ** @brief: Sets up signal handling for SIGINT.
 */
void setup_signal_handling(void)
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
 ** @brief: Reads user input, tokenizes it, and prepares for execution.
 **         Continuously prompts for input, processes commands, and cleans up memory.
 ** @return: Always returns NULL, as the function is structured for continuous input processing.
 */
t_token *process_input(void)
{
    char *input;
    t_token *tokens;

    input = read_input();
    while (input)
    {
        if (!*input)
        {
            free(input);
            input = read_input();
            continue;
        }
        tokens = get_tokens(input); 
        if (tokens)
        {
            /* ft_exec_tokens(tokens); */ //TODO: Implement this function
            print_tokens(tokens); /*debug*/
            free_tokens(tokens);
        }
        free(input);
        input = read_input();
    }
    return (NULL);
}
