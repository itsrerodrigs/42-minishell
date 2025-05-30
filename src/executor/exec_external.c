/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 14:41:47 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

/*
 * @brief Executes an external command with execve.
 * @param cmd_path Full path to the executable.
 * @param args Arguments including the command name.
 * @param envp Shell environment.
 */
int exec_external(t_shell *shell, char **args)
{
    char *cmd_path = find_executable(args[0], shell->envp);
    if (!cmd_path)
    {
        handle_cmd_not_found(shell, args[0]);
        return 127;
    }
    execve(cmd_path, args, shell->envp);
    perror("execve");
    free(cmd_path);
    return 1;
}