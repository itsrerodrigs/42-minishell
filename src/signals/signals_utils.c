/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:41:39 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 15:44:11 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_child_running = 0;

/*
* @brief: Saves the current SIGINT and SIGQUIT
* handlers and sets them to be ignored.
* @param old_int: Pointer to a struct sigaction
* to save the old SIGINT handler.
* @param old_quit: Pointer to a struct sigaction
* to save the old SIGQUIT handler.
 */
void	save_and_ignore_signals(struct sigaction *old_int,
		struct sigaction *old_quit)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, old_int);
	sigaction(SIGQUIT, &sa_ignore, old_quit);
}

/*
* @brief: Restores previously saved SIGINT and SIGQUIT handlers.
* @param old_int: Pointer to a struct sigaction holding the old SIGINT handler.
* @param old_quit: Pointer to a struct sigaction holding the old SIGQUIT handler.
*/
void	restore_signals(struct sigaction *old_int, struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}
/*
 * @brief: Sets SIGINT and SIGQUIT handlers to their default 
 * behavior for a child process.
 */

void	set_child_signals(void)
{
	struct sigaction	sa_dfl;

	ft_bzero(&sa_dfl, sizeof(sa_dfl));
	sa_dfl.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa_dfl, NULL);
	sigaction(SIGQUIT, &sa_dfl, NULL);
}

/*
 * @brief: Handles the SIGINT (Ctrl+C) signal.
 * @param signum: The signal number (SIGINT).
 */
void	sigint_handler(int signum)
{
	(void)signum;
	if (g_child_running == 1)
		write(1, "\n", 1);
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
/*
 * @brief: Sets up initial signal handling for the minishell.
 */

void	setup_signal_handling(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction for SIGINT failed");
		exit(EXIT_FAILURE);
	}
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("sigaction for SIGQUIT failed");
		exit(EXIT_FAILURE);
	}
}
