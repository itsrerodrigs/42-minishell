/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:16:51 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/03 13:09:12 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sig.h"
#include "executor.h"

void set_foreground_process(int fd, pid_t pgid)
{
    if (ioctl(fd, TIOCSPGRP, &pgid) == -1)
        perror("minishell: ioctl TIOCSPGRP failed");
}

void update_exit_status_from_wait_status(t_shell *shell, int raw_status)
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
void pipe_wait_children(t_shell *shell, pid_t last_pid)
{
    pid_t waited_pid;
    int status;

    while (1)
    {
        waited_pid = wait(&status);

        if (waited_pid < 0)
            break;
        if (waited_pid == last_pid)
			update_exit_status_from_wait_status(shell, status);
    }
}