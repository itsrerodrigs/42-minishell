/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:22:13 by renrodri          #+#    #+#             */
/*   Updated: 2025/04/28 18:26:05 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <limits.h>

/*incluir na libft da mari*/
int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}

/* retorna o caminho do diretório atual */
void builtin_pwd(char **args)
{
    (void)args;
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else
        perror("pwd: couldn't find current path");
}

/* executar o builtin */
int exec_builtin(char **args)
{
    if (ft_strcmp(args[0], "pwd") == 0)
    {
        builtin_pwd(args);
        return (1); /*se sim, indica que é um builtin*/
    }
    return (0); /*se não, indica que não é um builtin*/
}
