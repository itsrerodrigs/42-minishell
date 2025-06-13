/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:16:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 18:51:53 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_job_control(t_shell *shell)
{
	pid_t	pid;

	shell->shell_is_interactive = isatty(STDIN_FILENO);
	if (shell->shell_is_interactive)
	{
		shell->shell_terminal_fd = STDIN_FILENO;
		signal(SIGTTIN, SIG_IGN);
		signal(SIGTTOU, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		pid = getpid();
		if (setpgid(pid, pid) < 0)
		{
			perror("minishell: Couldn't put the shell in its own process group");
			exit(1);
		}
		if (tcsetpgrp(STDIN_FILENO, pid) < 0)
		{
			perror("minishell: tcsetpgrp failed");
			exit(1);
		}
		shell->shell_pgid = pid;
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
