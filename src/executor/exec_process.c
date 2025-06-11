/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:39:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 10:14:27 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path)
{
    char *cmd_path;

    if (caller_cmd_path)
        cmd_path = caller_cmd_path;
    else
    {
        cmd_path = find_executable(cmd->cmd, shell);
        if (!cmd_path)
        {
            ft_putstr_fd(cmd->cmd, STDERR_FILENO);
            ft_putendl_fd(": command not found", STDERR_FILENO);
            exit(127); // Child exits
        }
        
    }
    execve(cmd_path, cmd->args, shell->envp);
    perror("minishell: execve failed");
    if (!caller_cmd_path)
        free(cmd_path); 
    exit(EXIT_FAILURE);
}
