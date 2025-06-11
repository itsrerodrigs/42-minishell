/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:03:24 by marieli           #+#    #+#             */
/*   Updated: 2025/06/11 11:03:24 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


/**
 * @brief Constructs and returns the prompt string.
 */
static char	*display_prompt(void)
{
	char cwd[BUFSIZ];
	char *prompt;
	size_t prompt_size;

	if (isatty(fileno(stdin)))
	{
		getcwd(cwd, sizeof(cwd));
		prompt_size = ft_strlen(G) + ft_strlen(" minishell:~$ ")
			+ ft_strlen(RST) + 1;
		prompt = ft_malloc(prompt_size);
		if (!prompt)
			return (NULL);
		prompt[0] = '\0';
		ft_strlcat(prompt, G, prompt_size);
		ft_strlcat(prompt, " minishell:~$ ", prompt_size);
		ft_strlcat(prompt, RST, prompt_size);
		return (prompt);
	}
	return (ft_strdup("minishell:~$ "));
}

/**
 * @brief Reads user input from stdin using the readline library.
 */
char	*read_input(void)
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
	return (buf);
}
