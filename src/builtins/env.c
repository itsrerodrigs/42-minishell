/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:55:56 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:19:16 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/minishell.h"

int     builtin_env(t_shell *shell, char **args)
{
    int i;

    (void)args;
    if (!shell || !shell->envp)
        return (1);

    i = 0;
    while (shell->envp[i])
    {
        ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}