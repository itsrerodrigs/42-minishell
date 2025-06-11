/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/11 10:25:59 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


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
