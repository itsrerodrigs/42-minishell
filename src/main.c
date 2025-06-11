/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:08:01 by marieli           #+#    #+#             */
/*   Updated: 2025/06/11 11:08:01 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
#include "parser.h"
#include "sig.h"
#include "tokens.h"


static void	init_shell_job_control(t_shell *shell)
{
	shell->shell_is_interactive = isatty(STDIN_FILENO);
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

static void	init_shell_struct(t_shell *shell)
{
	shell->envp = NULL;
	shell->exit_status = 0;
	shell->current_cmd = NULL;
}

static void	s_process_loop(t_shell *shell)
{
	char *input;
	t_token *tokens;
	t_command *commands;

	while (1)
	{
		input = read_input();
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
		ft_exec(shell);
		free_tokens(tokens);
		free_commands(commands);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	(void)argc;
	(void)argv;

	init_shell_struct(&shell);
	shell.envp = dup_envp(envp);
	if (!shell.envp)
	{
		ft_putendl_fd("minishell: Failed to duplicate environment",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	setup_signal_handling();
	init_shell_job_control(&shell);
	p(C "Initializing Minishell..\n" RST);
	s_process_loop(&shell);
	free_envp(shell.envp);

	return (EXIT_SUCCESS);
}
