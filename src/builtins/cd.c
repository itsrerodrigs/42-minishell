/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:10:25 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../inc/minishell.h"

int     builtin_cd(t_shell *shell, char **args)
{
    char    *path;

    if (!args[1])
    {
        path = get_env_value(shell->envp, "HOME");
        if (!path)
        {
            ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
            return (1);
        }
    }
    else
        path = args[1];
    
    if (chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
        perror(path);
        return (1);
    }
    return (0);
}
