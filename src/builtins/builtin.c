/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:56 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/24 18:29:57 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../inc/minishell.h"

int ft_exit(char **args)
{
    int exit_code;
    
    exit_code = EXIT_SUCCESS;

    if (args[1]) 
    {
        exit_code = ft_atoi(args[1]);
        if (exit_code < 0)
            exit_code = EXIT_FAILURE;
    }
    p(RED "Shutting down...\n" RST);
    fflush(stdout);
    usleep(421337);
    exit(exit_code);
}

int ft_env(char **args)
{
    extern char **environ;
    int i;

    i = 0;
    (void)args;
    if (!environ)
        return(1);
    while (environ[i])
    {
        p("%s\n", environ[i]);
        i++;
    }
    return(0);
}
