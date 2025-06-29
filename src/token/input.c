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

static char	*display_prompt(void)
{
	char	cwd[BUFSIZ];
	char	*prompt;
	size_t	prompt_size;

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

static char	*read_a_line(t_shell *shell)
{
	char	*buf;
	char	*prompt;

	if (shell->shell_is_interactive)
	{
		prompt = display_prompt();
		buf = readline(prompt);
		free(prompt);
		if (buf && *buf)
			add_history(buf);
		return (buf);
	}
	buf = get_next_line(STDIN_FILENO);
	if (buf && ft_strlen(buf) > 0 && buf[ft_strlen(buf) - 1] == '\n')
		buf[ft_strlen(buf) - 1] = '\0';
	return (buf);
}

char	*read_input(t_shell *shell)
{
	char	*buf;

	buf = read_a_line(shell);
	if (!buf)
	{
		if (shell->shell_is_interactive)
			ft_putendl_fd("exit", STDOUT_FILENO);
		return (NULL);
	}
	return (buf);
}
