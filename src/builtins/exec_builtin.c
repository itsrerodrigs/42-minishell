/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:07 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/04 03:55:41 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_builtin *get_builtins(void)
{
    static t_builtin builtins[] = {
        {"cd", builtin_cd},
        {"echo", builtin_echo},
        {"env", builtin_env},
        {"exit", builtin_exit},
        {"unset", builtin_unset},
        {"pwd", builtin_pwd},
        {NULL, NULL}
    };
    return builtins;
}

static builtin_func find_builtin(char *cmd)
{
    t_builtin *builtins;
    int     i;

    builtins = get_builtins();
    i = 0;
    while (builtins[i].name)
    {
        if (ft_strncmp(cmd, builtins[i].name, ft_strlen(builtins[i].name)) == 0)
        {
            return builtins[i].func;
        }
        i++;
    }
    return NULL;
}

int     exec_builtin(t_shell *shell)
{
    char    *cmd_name;
    builtin_func func;
    int     exit_status;

    if (!shell || !shell->current_cmd || !shell->current_cmd->args[0])
        return (0);
    cmd_name = shell->current_cmd->args[0];
    func = find_builtin(cmd_name);
    if (func)
    {
        exit_status = func(shell, shell->current_cmd->args);
        exit(exit_status);
    }
        //return func(shell, shell->current_cmd->args);
    return (0);
}