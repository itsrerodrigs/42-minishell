/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 13:57:11 by mmariano         ###   ########.fr       */
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

/* -> nao usar mais, agora exec_command chama execve diretamente
 * @brief Launches a new process to execute a command.
 * 
 * @param shell The shell context.
 * @param cmd_path Full path to the executable.
 * @param args Arguments array.
 */
// void launch_process(t_shell *shell, t_command *cmd)
// {
// 	pid_t pid;
// 	char *cmd_path;
// 	char **args = cmd->args;

// 	cmd_path = find_executable(cmd->cmd, shell);
// 	if (!cmd_path)
// 	{
// 		ft_putstr_fd(cmd->cmd, STDERR_FILENO);
// 		ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 		shell->exit_status = 127;
// 		return;
// 	}

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		child_exec(cmd_path, args, cmd, shell->envp);
// 	}
// 	else if (pid < 0)
// 	{
// 		perror("fork");
// 		shell->exit_status = 1;
// 	}
// 	else
// 	{
// 		waitpid(pid, &shell->exit_status, 0);
// 		if (WIFEXITED(shell->exit_status))
// 			shell->exit_status = WEXITSTATUS(shell->exit_status);
// 	}
// 	free(cmd_path);
// }

void exec_command(t_shell *shell, t_command *cmd)
{
    char *cmd_path;

    if (shell->shell_is_interactive)
    {
        setpgid(0, 0);
        set_foreground_process(shell->shell_terminal_fd, getpgrp());
    }
    // IMPORTANT: NO exec_builtin CALL HERE.
    // If a built-in needs to be run in a child (e.g., due to piping/redirection),
    // that built-in execution should be explicitly handled *before* this function,
    // or this function should be split into exec_child_builtin and exec_child_external.
    // For now, assuming this path is only for external commands OR built-ins that
    // are explicitly delegated to child execution.

    // For built-ins that need to run in a child (e.g., `echo a | cat`),
    // you would add a check here or pass a flag from `exec_pipe_child`.
    // Example:
    // if (is_builtin(cmd->cmd->args[0])) { // you need a helper is_builtin
    //     execute_builtin_in_child_context(shell, cmd); // A new function for this
    //     exit(shell->exit_status);
    // }
    // if (exec_builtin(shell))
    //     exit(shell->exit_status);

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
