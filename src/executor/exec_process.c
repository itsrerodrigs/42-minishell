/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 03:57:41 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/*
 * @brief Executes the command in the child process using execve.
 * 
 * @param cmd_path Full path to the executable.
 * @param args Arguments array.
 * @param envp Environment variables array.
 * @note This function does not return; if execve fails, it exits.
 */
void child_exec(char *cmd_path, char **args, t_command *cmd, char **envp)
{
    (void)cmd;

    execve(cmd_path, args, envp);
    perror("minishell");
    exit(127);
}

/*
 * @brief Launches a new process to execute a command.
 * 
 * @param shell The shell context.
 * @param cmd_path Full path to the executable.
 * @param args Arguments array.
 */
void launch_process(t_shell *shell, t_command *cmd)
{
	pid_t pid;
	char *cmd_path;
	char **args = cmd->args;

	cmd_path = find_executable(cmd->cmd, shell);
	if (!cmd_path)
	{
		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		shell->exit_status = 127;
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		child_exec(cmd_path, args, cmd, shell->envp);
	}
	else if (pid < 0)
	{
		perror("fork");
		shell->exit_status = 1;
	}
	else
	{
		waitpid(pid, &shell->exit_status, 0);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
	}
	free(cmd_path);
}

void exec_command(t_shell *shell, t_command *cmd)
{
    char *cmd_path;

    exec_builtin(shell);
    cmd_path = find_executable(cmd->cmd, shell);
    if (!cmd_path)
    {
        ft_putstr_fd(cmd->cmd, STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        exit(127);
    }
    execve(cmd_path, cmd->args, shell->envp);
    perror("minishell: execve failed");
    free(cmd_path);
    exit(EXIT_FAILURE);
}
