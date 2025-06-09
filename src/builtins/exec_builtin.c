/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:07 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 18:02:45 by mmariano         ###   ########.fr       */
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
        {"export", builtin_export},
        {NULL, NULL}
    };
    return builtins;
}

builtin_func find_builtin(char *cmd) //tire o estatico pq va ser chamada por outras funçõe
{
    t_builtin *builtins;
    int     i;

    builtins = get_builtins();
    i = 0;
    while (builtins[i].name)
    {
        if (ft_strncmp(cmd, builtins[i].name, ft_strlen(builtins[i].name)) == 0 && ft_strlen(cmd) == ft_strlen(builtins[i].name))
        {
            return builtins[i].func;
        }
        i++;
    }
    return NULL;
}

int     exec_builtin(t_shell *shell)
{
    char            *cmd;
    builtin_func    func;
    int             builtin_return_status;

    if (!shell || !shell->current_cmd || !shell->current_cmd->args[0])
        return (0);
    
    cmd = shell->current_cmd->args[0];
    func = find_builtin(cmd);
    if (func)
    {
        builtin_return_status = func(shell, shell->current_cmd->args);
        shell->exit_status = builtin_return_status;
        return (1);
    }  
    return (0);
}
