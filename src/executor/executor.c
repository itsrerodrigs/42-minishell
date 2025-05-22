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

#include "../inc/minishell.h"

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

    /* Check if the command is a built-in.*/
/*     if (exec_builtin(shell))
        return; */

    /* TODO: Implement external command handling (fork + execve) */
    p(RED "Command not found: %s\n" RST, args[0]);
}

