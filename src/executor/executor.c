/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:42:04 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"
#include "executor.h"

/*
 * @brief Executes the current command from the shell state.
 * @param shell: Pointer to the shell structure containing the current command.
 * @return void.
 * @note This function first checks if the command is built-in by calling
 *       exec_builtin; if so, it returns immediately. Otherwise, it prints an error
 *       message indicating that the command is not found. External command handling
 *       (fork/execve) is yet to be implemented.
 */
void ft_exec(t_shell *shell)
{
    char **args;

    if (!shell || !shell->current_cmd)
        return;
    args = shell->current_cmd->args;
    if (!args || !args[0])
        return;
    if (exec_builtin(shell))
        return;
    exec_external(shell, args);
}

/*
 * @brief Handles the "command not found" error.
 * @param shell Shell context to update exit_status.
 * @param cmd Command that failed to execute.
 */
void handle_cmd_not_found(t_shell *shell, char *cmd)
{
    ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
    ft_putendl_fd(cmd, STDERR_FILENO);
    shell->exit_status = 127;
}



