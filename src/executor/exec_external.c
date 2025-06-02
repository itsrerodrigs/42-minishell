/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/02 18:10:46 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "sig.h"

/*
 * @brief Executes external (non-builtin) commands.
 * @param shell The shell context containing environment and status.
 * @param args The arguments array (args[0] is the command).
 * @return 0 on success, 127 if not found, 1 on error.
 */
// int exec_external(t_shell *shell, char **args)
// {
//     pid_t pid;
//     int status;
//     char *cmd_path;

//     cmd_path = find_executable(args[0], shell);
//     if (!cmd_path)
//     {
//         handle_cmd_not_found(shell, args[0]);
//         return (127);
//     }
//     pid = fork();
//     if (pid < 0)
//         return (perror("fork"), 1);
//     if (pid == 0)
//     {
//         execve(cmd_path, args, shell->envp);
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }
//     waitpid(pid, &status, 0);
//     shell->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
//     free(cmd_path);
//     return (0);
// }

// char get_executable_path(char *cmd, t_shell *shell)
// {
//     char *cmd_path;
    
//     cmd_path = find_executable(cmd, shell);
//     if (!cmd_path)
//         handle_cmd_not_found(shell, cmd);
//     return (*cmd_path);
// }

static void child_exec_logic(char *cmd_path, char **args, char **envp)
{
    set_child_default_signals();
    execve(cmd_path, args, envp);
    perror("execve failed");
    exit(127);
}

static void parent_wait_for_child(pid_t pid, t_shell *shell)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
    {
        shell->exit_status = 128 + WTERMSIG(status); // Exit status for signals
        if (WTERMSIG(status) == SIGINT)
            ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
    }
}

int exec_external(t_shell *shell, char **args)
{
    pid_t pid;
    char *cmd_path;
    struct sigaction old_int;
    struct sigaction old_quit;

    cmd_path = find_executable(args[0], shell);
    if (!cmd_path)
        return (127);
    g_child_running = 1;
    save_and_ignore_signals(&old_int, &old_quit); //nao tenho certeza
    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        restore_signals(&old_int, &old_quit);
        g_child_running = 0;
        free(cmd_path);
        return (1);
    }
    if (pid == 0)
    {
        child_exec_logic(cmd_path, args, shell->envp);
    }
    else
    {
        parent_wait_for_child(pid, shell);
        restore_signals(&old_int, &old_quit);
        g_child_running = 0;
        free(cmd_path);
    }
    return (0);
}
