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
	printf(C "Initializing Minishell..\n" RST);
	s_process_loop(&shell);
	rl_clear_history();
	free_envp(shell.envp);

	return (EXIT_SUCCESS);
}
