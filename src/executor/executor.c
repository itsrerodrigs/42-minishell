/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:56:16 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
remove the global variables as soon as possible
*/

t_builtin g_builtin[] = 
{
//	{.builtin_name="echo", .foo=shell_echo},
//	{.builtin_name="env", .foo=shell_env},
	{.builtin_name="exit", .foo=ft_exit},
	{.builtin_name= NULL},
};

int status = 0;

//my comand is a builtin? -> call it directly
//if not, call execvp: fork+execvp+wait

void    ft_exec(char **args)
{
    int     i;
    //int     status;
    const char *curr;

    if (args == NULL || args[0] == NULL)
        return;

    i = 0;
    while ((curr = g_builtin[i].builtin_name) != NULL)
    {
        if (!ft_strncmp(curr, args[0], ft_strlen(curr)))
        {
            status = g_builtin[i].foo(args);
            return;
        }
        ++i;
    }
    p(RED "Command not found: %s\n" RST, args[0]); // Debug or error message
}


// void ft_launch(char **args)
// {
// 	if (ft_fork() == CELL_Jr)
// 		ft_execvp(args[0], args);
// 	else
// 		ft_wait(&status);

// }