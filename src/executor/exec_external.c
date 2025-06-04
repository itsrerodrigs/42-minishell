/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 13:23:22 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "sig.h"
#include "builtins.h"

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

/* static void child_exec_logic(char *cmd_path, char **args, char **envp, t_shell *shell)
{
    st_child_signals();
    if (shell->shell_is_interactive)
    {
        setpgid(0, 0);
        set_foreground_process(shell->shell_terminal_fd, getpgrp());
    }
    execve(cmd_path, args, envp);
    perror("minishell: execve failed");
    exit(127);
} */

/* static void parent_wait_for_child(pid_t pid, t_shell *shell)
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
} */


static void handle_child_process(t_shell *shell, char *cmd_path,  char **args) 
{
    set_child_signals();
    execve(cmd_path, args, shell->envp);
    perror("minishell: execve failed");
    free(cmd_path); // Only if execve fails
    exit(EXIT_FAILURE);
}

static void handle_parent_process(t_shell *shell, pid_t pid, char *cmd_path, t_old_signals *old_sa) 
{
    int raw_status;

    if (shell->shell_is_interactive) {
        set_foreground_process(shell->shell_terminal_fd, pid);
    }

    waitpid(pid, &raw_status, WUNTRACED);

    if (shell->shell_is_interactive) {
        set_foreground_process(shell->shell_terminal_fd, shell->shell_pgid);
    }

    update_exit_status_from_wait_status(shell, raw_status);
    restore_signals(&old_sa->int_sa, &old_sa->quit_sa);
    g_child_running = 0;
    free(cmd_path);
}

int exec_external(t_shell *shell, char **args) 
{
    char        *cmd_path;
    pid_t       pid;
    t_old_signals old_sa;

    // Phase 1: Pre-execution setup and fork
    cmd_path = find_executable(args[0], shell);
    if (!cmd_path)
        return (127);

    g_child_running = 1;
    save_and_ignore_signals(&old_sa.int_sa, &old_sa.quit_sa);

    pid = fork();
    if (pid < 0) {
        perror("minishell: fork failed");
        restore_signals(&old_sa.int_sa, &old_sa.quit_sa);
        g_child_running = 0;
        free(cmd_path);
        return (1);
    }

    // Phase 2: Handle child or parent logic
    if (pid == 0)
        handle_child_process(shell, cmd_path, args);
    else
        handle_parent_process(shell, pid, cmd_path, &old_sa);
    return (0);
}
