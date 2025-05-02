/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:56:24 by renrodri          #+#    #+#             */
/*   Updated: 2025/04/28 18:26:03 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void    builtin_echo(char **args)
{
    int i;
    int newline;

    i = 1;
    newline = 1;

   while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
   {
        int j;

        j = 2;
        while (args[i][j] == 'n')
            j++;
        if (args[i][j] != '\0')
            break;
        newline = 0;
        i++;
   }

    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
            i++;
    }
    if (newline)
        printf("\n");
}

int exec_builtin(char **args)
{
    if (args[0] == NULL)
        return (0);

    if (ft_strcmp(args[0], "echo") == 0)
    {
        builtin_echo(args);
        return (1);
    }
    return (0);
}