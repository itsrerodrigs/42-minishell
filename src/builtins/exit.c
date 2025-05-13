/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/09 13:32:44 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


/*
 * @brief: Built-in exit command for minishell. It converts the supplied argument
 *         into an exit code (defaulting to EXIT_SUCCESS) and exits the program.
 * @param args: a NULL-terminated array of strings with the command arguments.
 * @return: this function does not return as it calls exit() after cleanup.
 * @note: The function also performs a short delay before exiting.
 */
int ft_exit(char **args)
{
    int exit_code;
    
    exit_code = EXIT_SUCCESS;

    if (args && args[1]) 
    {
        exit_code = ft_atoi(args[1]);
        if (exit_code < 0)
            exit_code = EXIT_FAILURE;
    }
    p(RED "Shutting down...\n" RST);
    fflush(stdout);
    usleep(421337);
    if (args && args[0])
        free(args[0]);
    exit(exit_code);
}
