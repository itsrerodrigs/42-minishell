/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:44 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 23:05:19 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @brief Executes a single command that is a builtin in the parent process.
 */
static int	exec_parent_builtin(t_shell *shell, t_command *cmd)
{
	int				saved_stdin;
	int				saved_stdout;
	int				exit_code;
	builtin_func	func;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	exit_code = 1;
	if (apply_redirections(cmd) == 0)
	{
		func = find_builtin(cmd->args[0]);
		if (func)
			exit_code = func(shell, cmd->args);
	}
	shell->exit_status = exit_code;
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		perror("dup2 restore stdin failed");
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		perror("dup2 restore stdout failed");
	close(saved_stdin);
	close(saved_stdout);
	return (1);
}

/*
 * @brief Forks the process and executes the child logic.
 */
static pid_t	fork_and_run_child(t_shell *shell, t_command *cmd, int *p,
		int *pfd)
{
	pid_t	pid;

	if (cmd->is_pipe)
		if (pipe(p) == -1)
		{
			perror("minishell: pipe failed");
			return (-1);
		}
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		if (p[0] != -1)
		{
			close(p[0]);
			close(p[1]);
		}
		return (-1);
	}
	if (pid == 0)
		exec_pipe_child(shell, cmd, *pfd, p);
	return (pid);
}

/**
 * @brief Handles forking and parent-side logic for a single piped command.
 */
static int	run_forked_cmd(t_shell *shell, t_command *cmd,
				int *p_fd, int *l_pid)
{
	pid_t	pid;
	int		pipe_fds[2];

	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
	pid = fork_and_run_child(shell, cmd, pipe_fds, p_fd);
	if (pid < 0)
		return (-1);
	handle_parent_fds(pipe_fds, p_fd, cmd->is_pipe);
	*l_pid = pid;
	return (0);
}

/**
 * @brief The main loop for executing a pipeline of one or more commands.
 */
static int	exec_pipe_loop(t_shell *shell, t_command *cmd_list)
{
	t_command	*current_cmd;
	int			prev_pipe_read_fd;
	int			last_pid;

	current_cmd = cmd_list;
	prev_pipe_read_fd = -1;
	last_pid = -1;
	while (current_cmd)
	{
		if (is_builtin_parent_executable(current_cmd))
			exec_parent_builtin(shell, current_cmd);
		else
		{
			if (run_forked_cmd(shell, current_cmd,
					&prev_pipe_read_fd, &last_pid) < 0)
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
 */
void	exec_pipeline(t_shell *shell, t_command *first_cmd)
{
	t_old_signals	old_sa;
	int				last_executed_pid;

	g_child_running = 1;
	save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);
	last_executed_pid = exec_pipe_loop(shell, first_cmd);
	if (shell->shell_is_interactive)
		set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);
	wait_for_children(shell, last_executed_pid);
	restore_signals(&old_sa.int_sa, &old_sa.quit_sa);
	g_child_running = 0;
}
