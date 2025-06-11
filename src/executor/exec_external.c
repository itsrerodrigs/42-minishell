/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:41:47 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 10:13:54 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "sig.h"
#include "builtins.h"


static void handle_child_process(t_shell *shell, char *cmd_path,  char **args) 
{
    set_child_signals();
    setpgid(0, 0);
    if (apply_redirections(shell->current_cmd) != 0) // Pass shell->current_cmd to get redirs
        exit(1);
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
    {
        ft_putstr_fd(args[0], STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        shell->exit_status = 127;
        return (127);
    }
        

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
