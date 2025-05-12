/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:22:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/02 17:07:23 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <stdio.h>

int builtin_pwd(t_shell *shell, char **args)
{
    char cwd[PATH_MAX];

    (void)shell; // `shell` não é usado nesta função
    (void)args;  // Ignora os argumentos

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putendl_fd(cwd, STDOUT_FILENO);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1); 
    }
}