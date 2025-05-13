/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:29:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/12 21:14:02 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
t_token *read_input(void)
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
        ft_exit(NULL);
    }
    return (create_token(buf));
}
