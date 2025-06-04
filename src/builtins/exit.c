/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/04 13:27:11 by mmariano         ###   ########.fr       */
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
/* int builtin_exit(t_shell *shell, char **args)
{
    int exit_code;
    
    exit_code = EXIT_SUCCESS;
    (void)shell;

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
} */

static int is_valid_exit_arg(const char *str)
{
    int i;

    i = 0;
    if (!str || !str[i])
        return (0);
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return (0);
    while (str[i])
    {
        if (!ft_isdigit(str[i])) 
            return (0);
        i++;
    }
    return (1);
}

static int handle_too_many_exit_args(void)
{
    ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
    return (1);
}

static void handle_non_numeric_exit_arg(const char *arg)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd((char *)arg, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
    exit(255);}

int builtin_exit(t_shell *shell, char **args)
{
    int exit_code;
    int arg_count;

    (void)shell;
    exit_code = EXIT_SUCCESS;

    arg_count = 0;
    while (args[arg_count])
        arg_count++;
    if (arg_count > 2)
        return (handle_too_many_exit_args());
    if (args[1])
    {
        if (!is_valid_exit_arg(args[1]))
            handle_non_numeric_exit_arg(args[1]);
        exit_code = ft_atoi(args[1]);
    }
    // printf(RED "Shutting down...\n" RST); 
    ft_putendl_fd("exit", STDERR_FILENO);
    fflush(stdout);
    // usleep(421337);
    exit(exit_code);
}
