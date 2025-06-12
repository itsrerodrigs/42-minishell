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
 * @brief Reads a line of input, using readline for interactive mode.
 */
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

/**
 * @brief Reads user input from stdin.
 */
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

void	init_shell_job_control(t_shell *shell)
{
	shell->shell_is_interactive = isatty(STDIN_FILENO);
	if (shell->shell_is_interactive)
	{
		shell->shell_terminal_fd = STDIN_FILENO;
		while (tcgetpgrp(shell->shell_terminal_fd) != (shell->shell_pgid = getpgrp()))
			kill(-shell->shell_pgid, SIGTTIN);
		setpgid(0, 0);
		shell->shell_pgid = getpgrp();
		set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
	}
}

void	init_shell_struct(t_shell *shell)
{
	shell->envp = NULL;
	shell->exit_status = 0;
	shell->current_cmd = NULL;
	shell->should_exit = false;
}

void	s_process_loop(t_shell *shell)
{
	char *input;
	t_token *tokens;
	t_command *commands;

	while (1)
	{
		input = read_input(shell);
		if (!input)
			break ;
		tokens = get_tokens(input, shell);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		commands = parse_tokens(tokens, shell);
		shell->current_cmd = commands;
		if (commands)
			ft_exec(shell);
		free_tokens(tokens);
		free_commands(commands);
		free(input);
		if (shell->should_exit)
			break;
	}
}
