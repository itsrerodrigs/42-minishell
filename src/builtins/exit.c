/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/12 18:13:37 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * @brief Checks if an argument string contains only digits (and an optional sign).
 */
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

/**
 * @brief Prints an error and exits if the argument for exit is not numeric.
 */
static int handle_non_numeric_exit_arg(const char *arg)
{
    ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
    ft_putstr_fd((char *)arg, STDERR_FILENO);
    ft_putendl_fd(": numeric argument required", STDERR_FILENO);
    return (1);
}

/**
 * @brief Exits the shell, optionally with a specific exit code.
 */
int	builtin_exit(t_shell *shell, char **args)
{
	int	arg_count;
	int final_exit_code;

	final_exit_code = shell->exit_status;
	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (shell->shell_is_interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (arg_count > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		shell->exit_status = 1; 
		return (1);
	}
	if (args[1])
	{
		if (!is_valid_exit_arg(args[1]))
		{
			handle_non_numeric_exit_arg(args[1]);
			final_exit_code = 255;
		}
		else
		{
			final_exit_code = ft_atoi(args[1]);
		}
	}
	shell->exit_status = final_exit_code;
	shell->should_exit = true;
	return (0);
}

