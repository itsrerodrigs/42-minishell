/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:16:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 16:24:56 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_job_control(t_shell *shell)
{
	shell->shell_is_interactive = isatty(STDIN_FILENO);
	if (shell->shell_is_interactive)
	{
		shell->shell_terminal_fd = STDIN_FILENO;
		while (1)
		{
			shell->shell_pgid = getpgrp();
			if (tcgetpgrp(shell->shell_terminal_fd) == shell->shell_pgid)
				break ;
			kill(-shell->shell_pgid, SIGTTIN);
		}
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
	char		*input;
	t_token		*tokens;
	t_command	*commands;

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
			break ;
	}
}
