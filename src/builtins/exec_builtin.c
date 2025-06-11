/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:07 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:36:39 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_builtin	*get_builtins(void)
{
    static t_builtin builtins[] = {
        {"cd", builtin_cd},
        {"echo", builtin_echo},
        {"env", builtin_env},
        {"exit", builtin_exit},
        {"unset", builtin_unset},
        {"pwd", builtin_pwd},
        {"export", builtin_export},
        {NULL, NULL}
    };
    return builtins;
}

builtin_func	find_builtin(char *cmd)
{
	int		i;
	t_builtin *builtins;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(cmd, builtins[i].name, ft_strlen(builtins[i].name)) ==
			0 && ft_strlen(cmd) == ft_strlen(builtins[i].name))
		{
			return (builtins[i].func);
		}
		i++;
	}
	return (NULL);
}


/*
 * @brief Saves the original STDIN and STDOUT file descriptors.
 * @param orig_stdin Pointer to store original STDIN FD.
 * @param orig_stdout Pointer to store original STDOUT FD.
 * @return 0 on success, 1 on failure (e.g., dup failed).
 */
static int s_save_original_fds(int *orig_stdin, int *orig_stdout)
{
    *orig_stdin = dup(STDIN_FILENO);
    *orig_stdout = dup(STDOUT_FILENO);
    if (*orig_stdin == -1 || *orig_stdout == -1) {
        perror("minishell: dup failed in builtin setup");
        if (*orig_stdin != -1) close(*orig_stdin);
        if (*orig_stdout != -1) close(*orig_stdout);
        return (1);
    }
    return (0);
}

/*
 * @brief Restores the original STDIN and STDOUT file descriptors and closes saved FDs.
 * @param orig_stdin Original STDIN FD.
 * @param orig_stdout Original STDOUT FD.
 */
static void s_restore_fds(int orig_stdin, int orig_stdout)
{
    dup2(orig_stdin, STDIN_FILENO);
    dup2(orig_stdout, STDOUT_FILENO);
    close(orig_stdin);
    close(orig_stdout);
}

/*
 * @brief Applies redirections and executes the built-in function.
 * Sets shell->exit_status based on builtin's return.
 * @param shell The shell context.
 * @param func The builtin function pointer to execute.
 * @return 1 if builtin successfully executed (regardless of its internal exit status).
 * -1 if redirection application failed (exit status is set in shell).
 */
static int s_perform_builtin_io_and_exec(t_shell *shell, builtin_func func)
{
    int builtin_exit_status;

    if (apply_redirections(shell->current_cmd) != 0) 
    {
        shell->exit_status = 1; 
        return (-1);
    }
    builtin_exit_status = func(shell, shell->current_cmd->args);
    shell->exit_status = builtin_exit_status; 
    return (1);
}

/*
 * @brief Executes a built-in command with proper I/O redirection.
 * @param shell The shell context.
 * @return 1 if a built-in was found and executed (regardless of its success/failure),
 * 0 if no built-in was found or if initial setup failed.
 */
int exec_builtin(t_shell *shell)
{
    char            *cmd;
    builtin_func    func;
    int             orig_stdin;
    int             orig_stdout;
    int             exec_result;

    if (!shell || !shell->current_cmd || !shell->current_cmd->args || !shell->current_cmd->args[0])
        return (0);

    cmd = shell->current_cmd->args[0];
    func = find_builtin(cmd);
    if (!func) 
        return (0);
    if (s_save_original_fds(&orig_stdin, &orig_stdout) != 0)
        return (0);
    exec_result = s_perform_builtin_io_and_exec(shell, func);
    s_restore_fds(orig_stdin, orig_stdout);
    if (exec_result == -1)
        return (1); 
    return (1); 
}
