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

// You can add this function to src/executor/executor.c

/*
 * @brief Processes all heredoc redirections for a list of commands before execution.
 * @param commands The first command in the list.
 * @param shell The shell context.
 * @return 0 on success, 1 on failure (e.g., heredoc read failed).
 */
static int process_all_heredocs(t_command *commands, t_shell *shell)
{
    t_command  *current_cmd;
    t_redirect *redir_node;

    current_cmd = commands;
    while (current_cmd)
    {
        redir_node = current_cmd->redirs;
        while (redir_node)
        {
            if (redir_node->type == REDIR_HEREDOC)
            {
                // This function call handles the forking and reading
                current_cmd->heredoc_pipe_read_fd = process_heredoc(redir_node->filename);
                if (current_cmd->heredoc_pipe_read_fd == -1)
                {
                    shell->exit_status = 1;
                    return (1); // Stop if any heredoc fails
                }
            }
            redir_node = redir_node->next;
        }
        current_cmd = current_cmd->next;
    }
    return (0);
}


// In: src/executor/executor.c

void ft_exec(t_shell *shell)
{
    char **args;

    if (!shell || !shell->current_cmd)
        return;

    // *** ADD THIS BLOCK ***
    // Pre-process all heredocs before any forking or execution.
    if (process_all_heredocs(shell->current_cmd, shell) != 0)
    {
        // A heredoc failed, so we stop execution.
        return;
    }
    // *** END OF NEW BLOCK ***

    args = shell->current_cmd->args;
    if (!args || !args[0])
        return;

    if (shell->current_cmd->next)
    {
        exec_pipeline(shell, shell->current_cmd);
        return;
    }

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


