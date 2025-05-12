<<<<<<< HEAD
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
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 17:21:30 by renrodri         ###   ########.fr       */
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

int     builtin_exit(t_shell *shell, char **args)
{
    int exit_code;

    (void)shell;
    if (args[1])
    {
        if (!ft_isdigit_str(args[1]))
        {
            ft_putendl_fd("exit: numeric argument required", STDERR_FILENO);
            exit(255);
        }
        if (args[2])
        {
            ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
            return (1);
        }
        exit_code = ft_atoi(args[1]);
    }
    else
        exit_code = 0;
    
    ft_putendl_fd("exit", STDOUT_FILENO);
    exit(exit_code);
}
>>>>>>> builtins-test
