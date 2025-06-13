/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:16:51 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 19:40:55 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 ** @brief: Sets the foreground process group for a given terminal.
 ** @param fd: The file descriptor of the controlling terminal (e.g.,
	STDIN_FILENO).
 ** @param pgid: The process group ID to set as the foreground.
 ** @return: void
 */
void	set_foreground_process(int fd, pid_t pgid)
{
	int	ret;

	ret = ioctl(fd, TIOCSPGRP, &pgid);
	while (ret == -1 && errno == EINTR)
	{
		ret = ioctl(fd, TIOCSPGRP, &pgid);
	}
	if (ret == -1)
		perror("minishell: ioctl TIOCSPGRP failed");
}

/*
 ** @brief: Updates the shell's exit status based on a raw wait status.
 ** @param shell: Pointer to the shell's main structure.
 ** @param raw_status: The raw status value returned by wait/waitpid.
 ** @return: void
 */
void	update_exit_status_from_wait_status(t_shell *shell, int raw_status)
{
	if (WIFEXITED(raw_status))
		shell->exit_status = WEXITSTATUS(raw_status);
	else if (WIFSIGNALED(raw_status))
	{
		shell->exit_status = 128 + WTERMSIG(raw_status);
		if (WTERMSIG(raw_status) == SIGQUIT)
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}

/* @brief: Waits for all child processes in a pipeline to complete.
 * @param shell: Pointer to the shell's main structure.
 * @param last_pid: The PID of the last process in the pipeline to 
 * track its status.
 * @return: void
 */
void	pipe_wait_children(t_shell *shell, pid_t last_pid)
{
	pid_t	waited_pid;
	int		status;

	if (last_pid != 1)
	{
		waited_pid = waitpid(last_pid, &status, 0);
		if (waited_pid == last_pid)
		{
			update_exit_status_from_wait_status(shell, status);
		}
	}
	while (1)
	{
		waited_pid = waitpid(-1, &status, WNOHANG);
		if (waited_pid <= 0)
			break ;
		(void) status;
	}
}
