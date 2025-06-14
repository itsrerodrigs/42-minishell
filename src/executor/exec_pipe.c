/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 21:19:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_parent_builtin(t_shell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;
	int	builtin_exec_status;

	s_save_fds_for_builtin(&saved_stdin, &saved_stdout);
	builtin_exec_status = s_execute_and_set_status(shell, cmd);
	s_restore_and_close_fds(saved_stdin, saved_stdout);
	(void)builtin_exec_status;
	return (1);
}

// src/executor/exec_pipe.c

/*
 * @brief Forks the process and executes the child logic.
 * We need to add the pgid to this function's parameters.
 */
static pid_t	fork_and_run_child(t_shell *shell, t_command *cmd, int *p,
		int *pfd, pid_t *pgid) // Add pid_t *pgid
{
	pid_t	pid;

	if (s_handle_pipe_creation(p, cmd->is_pipe) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (s_handle_fork_failure(p));
	if (pid == 0)
	{
		// Pass the pgid to the child. If it's 0, the child will
		// use its own PID to start a new group.
		exec_pipe_child(shell, cmd, *pfd, p, *pgid);
	}
	else if (*pgid == 0)
	{
		// In the parent, if the pgid is not set, set it to the
		// PID of the first child.
		*pgid = pid;
	}
	// All children will be set to this group.
	setpgid(pid, *pgid);
	return (pid);
}

/*
 * @brief Update to pass the pgid pointer.
 */
static int	run_forked_cmd(t_shell *shell, t_command *cmd,
				int *p_fd, int *l_pid, pid_t *pgid) // Add pid_t *pgid
{
	pid_t	pid;
	int		pipe_fds[2];

	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	pid = fork_and_run_child(shell, cmd, pipe_fds, p_fd, pgid); // Pass pgid
	if (pid < 0)
		return (-1);
	handle_parent_fds(pipe_fds, p_fd, cmd->is_pipe);
	*l_pid = pid;
	return (0);
}

/**
 * @brief The main loop for executing a pipeline of one or more commands.
 * Update to manage the pgid.
 */
static int	exec_pipe_loop(t_shell *shell, t_command *cmd_list, pid_t *pgid) // Add pid_t *pgid
{
	t_command	*current_cmd;
	int			prev_pipe_read_fd;
	int			last_pid;

	current_cmd = cmd_list;
	prev_pipe_read_fd = -1;
	last_pid = -1;
	*pgid = 0; // Initialize the pipeline's process group ID to 0
	while (current_cmd)
	{
		if (is_builtin_parent_executable(current_cmd))
			exec_parent_builtin(shell, current_cmd);
		else
		{
			if (run_forked_cmd(shell, current_cmd,
					&prev_pipe_read_fd, &last_pid, pgid) < 0) // Pass pgid
				break ;
		}
		current_cmd = current_cmd->next;
	}
	if (prev_pipe_read_fd != -1)
		close(prev_pipe_read_fd);
	return (last_pid);
}

/**
 * @brief Sets up signals and executes a command pipeline.
 * Update to handle terminal control correctly.
 */
void	exec_pipeline(t_shell *shell, t_command *first_cmd)
{
	t_old_signals	old_sa;
	int				last_executed_pid;
	pid_t			pipeline_pgid;

	g_child_running = 1;
	save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);
	last_executed_pid = exec_pipe_loop(shell, first_cmd, &pipeline_pgid);
	if (shell->shell_is_interactive && pipeline_pgid > 0)
		set_foreground_process(shell->shell_terminal_fd, pipeline_pgid);

	wait_for_children(shell, last_executed_pid);
	if (shell->shell_is_interactive)
		set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);

	restore_signals(&old_sa.int_sa, &old_sa.quit_sa);
	g_child_running = 0;
}
