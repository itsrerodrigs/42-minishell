/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:02:13 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Logic for the child process to set up signals and execute a command.
 */
static void	handle_child_process(t_shell *shell, char *cmd_path, char **args)
{
	set_child_signals();
	setpgid(0, 0);
	if (apply_redirections(shell->current_cmd) != 0)
		exit(1);
	execve(cmd_path, args, shell->envp);
	perror("minishell: execve failed");
	free(cmd_path);
	exit(EXIT_FAILURE);
}

/**

	* @brief Logic for the parent process to wait for the child and set exit status.
 */
static void	handle_parent_process(t_shell *s, pid_t pid, char *path,
		t_old_signals *sa)
{
	int	raw_status;

	if (s->shell_is_interactive)
		set_foreground_process(s->shell_terminal_fd, pid);
	waitpid(pid, &raw_status, WUNTRACED);
	if (s->shell_is_interactive)
		set_foreground_process(s->shell_terminal_fd, s->shell_pgid);
	update_exit_status_from_wait_status(s, raw_status);
	restore_signals(&sa->int_sa, &sa->quit_sa);
	g_child_running = 0;
	free(path);
}

/**
 * @brief Sets up signals, forks the process, and handles fork errors.
 */
static pid_t	fork_and_prep_signals(t_old_signals *sa, char *cmd_path)
{
	pid_t	pid;

	g_child_running = 1;
	save_and_ignore_signals(&sa->int_sa, &sa->quit_sa);
	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork failed");
		restore_signals(&sa->int_sa, &sa->quit_sa);
		g_child_running = 0;
		free(cmd_path);
	}
	return (pid);
}

/**
 * @brief Executes external (non-builtin) commands.
 */
int	exec_external(t_shell *shell, char **args)
{
	char			*cmd_path;
	pid_t			pid;
	t_old_signals	old_sa;

	cmd_path = find_executable(args[0], shell);
	if (!cmd_path)
	{
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		shell->exit_status = 127;
		return (127);
	}
	pid = fork_and_prep_signals(&old_sa, cmd_path);
	if (pid < 0)
		return (1);
	if (pid == 0)
		handle_child_process(shell, cmd_path, args);
	else
		handle_parent_process(shell, pid, cmd_path, &old_sa);
	return (0);
}
