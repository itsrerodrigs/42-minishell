/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:24:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/04/28 17:38:33 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

void    builtin_cd(char **args)
{
    const char *path;

    if (args[1] == NULL)
    {
        path = getenv("HOME");
        if (path == NULL)
        {
            perror("cd: HOME not set");
        }
        return;
    }
    else
        path = args[1];
    
    if (chdir(path) != 0)
        perror("cd: couldn't set a directory");
}

int exec_builtin (char **args)
{
    if (args[0] == NULL)
        return (0);
    if (ft_strcmp(args[0], "cd") == 0)
    {
        builtin_cd(args);
        return (1);
    }
}