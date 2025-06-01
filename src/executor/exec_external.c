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
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * @brief Executes external (non-builtin) commands.
 * @param shell The shell context containing environment and status.
 * @param args The arguments array (args[0] is the command).
 * @return 0 on success, 127 if not found, 1 on error.
 */
int exec_external(t_shell *shell, char **args)
{
    pid_t pid;
    int status;
    char *cmd_path;

    cmd_path = find_executable(args[0], shell);
    if (!cmd_path)
    {
        handle_cmd_not_found(shell, args[0]);
        return (127);
    }
    pid = fork();
    if (pid < 0)
        return (perror("fork"), 1);
    if (pid == 0)
    {
        execve(cmd_path, args, shell->envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    waitpid(pid, &status, 0);
    shell->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
    free(cmd_path);
    return (0);
}
