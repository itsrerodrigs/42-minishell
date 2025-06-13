/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:34:22 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/13 11:52:41 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Prints "exit" to stdout if the shell is interactive.
 * @param shell A pointer to the shell's main structure.
 */
static void	ft_print_exit_message(t_shell *shell)
{
	if (shell->shell_is_interactive)
		ft_putendl_fd("exit", STDOUT_FILENO);
}

/*
 * @brief Handles the case of "too many arguments" for the exit command.
 * @param shell A pointer to the shell's main structure.
 * @return 1, indicating an error for the builtin command.
*/

static int	handle_too_many_args(t_shell *shell)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	shell->exit_status = 1;
	return (1);
}

/**
 * @brief Processes the numeric argument for the exit command.
 * @param shell A pointer to the shell's main structure.
 * @param arg The argument string.
 * @return The exit status to be set for the shell.
 */
static int	process_exit_argument(t_shell *shell, const char *arg)
{
	long long	exit_val;

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

/*
 * @brief Exits the shell, optionally with a specific exit code.
 */
int	builtin_exit(t_shell *shell, char **args)
{
	int	arg_count;
	int	builtin_retun_status;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	ft_print_exit_message(shell);
	if (arg_count > 2)
	{
		builtin_retun_status = handle_too_many_args(shell);
	}
	else
	{
		while (builtin_retun_status == 0)
			if (arg_count == 2)
				shell->exit_status = process_exit_argument(shell, arg[1]);
		else
				shell->exit_status = shell->exit_status;
	}
	shell->should_exit = true;
	return (builtin_retun_status);
}
