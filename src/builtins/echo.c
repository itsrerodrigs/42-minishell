/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:56:24 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:05:02 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/minishell.h"

int     builtin_echo(t_shell *shell, char **args)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    (void)shell;

    if (args[i] && ft_strncmp(args[i], "-n", ft_strlen("-n") + 1) == 0)
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], STDOUT_FILENO);
        if (args[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return (0);
}