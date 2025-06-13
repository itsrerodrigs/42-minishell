/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 17:49:32 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	ft_print_exit_message(t_shell *shell)
{
	if (shell->shell_is_interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
}

static int	handle_too_many_args(t_shell *shell)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}

static int	process_exit_argument(t_shell *shell, const char *arg)
{
	long long	exit_val;

	(void)shell;
	if (!is_valid_exit_arg(arg))
	{
		handle_non_numeric_exit_arg(arg);
		return (255);
	}
	else
	{
		exit_val = ft_atoi(arg);
		return ((unsigned char)exit_val);
	}
}

int	builtin_exit(t_shell *shell, char **args)
{
	int	arg_count;
	int	builtin_retun_status;

	arg_count = 0;
	builtin_retun_status = 0;
	while (args[arg_count])
		arg_count++;
	ft_print_exit_message(shell);
	if (arg_count > 2)
		builtin_retun_status = handle_too_many_args(shell);
	else
	{
		while (builtin_retun_status == 0)
			if (arg_count == 2)
				shell->exit_status = process_exit_argument(shell, args[1]);
		else
				shell->exit_status = shell->exit_status;
	}
	shell->should_exit = true;
	return (builtin_retun_status);
}
