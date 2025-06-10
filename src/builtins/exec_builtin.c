/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:36:07 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/10 15:27:02 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_builtin	*get_builtins(void)
{
    static t_builtin builtins[] = {
        {"cd", builtin_cd},
        {"echo", builtin_echo},
        {"env", builtin_env},
        {"exit", builtin_exit},
        {"unset", builtin_unset},
        {"pwd", builtin_pwd},
        {"export", builtin_export},
        {NULL, NULL}
    };
    return builtins;
}

builtin_func	find_builtin(char *cmd)
{
	int		i;
	t_builtin *builtins;

	builtins = get_builtins();
	i = 0;
	while (builtins[i].name)
	{
		if (ft_strncmp(cmd, builtins[i].name, ft_strlen(builtins[i].name)) ==
			0 && ft_strlen(cmd) == ft_strlen(builtins[i].name))
		{
			return (builtins[i].func);
		}
		i++;
	}
	return (NULL);
}

bool is_builtin_parent_executable(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	if (ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0]) +1) ||
		ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0]) + 1) ||
		ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0]) + 1) ||
		ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0]) + 1))
		{
			return (!cmd->is_pipe && cmd->prev_pipe_read_fd == -1);
		}
		return (false);
}

// int	exec_builtin(t_shell *shell)
// {
// 	char		*cmd;
// 	int		builtin_return_status;
// 	builtin_func	func;

// 	if (!shell || !shell->current_cmd || !shell->current_cmd->args[0])
// 		return (0);
// 	cmd = shell->current_cmd->args[0];
// 	func = find_builtin(cmd);
// 	if (func)
// 	{
// 		builtin_return_status = func(shell, shell->current_cmd->args);
// 		shell->exit_status = builtin_return_status;
// 		return (1);
// 	}
// 	return (0);
// }


int exec_builtin(t_shell *shell)
{
    char            *cmd;
    builtin_func    func;
    int             builtin_return_status;
    int             original_stdin = dup(STDIN_FILENO);  
    int             original_stdout = dup(STDOUT_FILENO);

    if (original_stdin == -1 || original_stdout == -1) 
	{
        perror("minishell: dup failed in builtin redirection setup");
        if (original_stdin != -1) close(original_stdin);
        if (original_stdout != -1) close(original_stdout);
        return (0); 
    }

    if (!shell || !shell->current_cmd || !shell->current_cmd->args || !shell->current_cmd->args[0])
    {
        close(original_stdin);
        close(original_stdout);
        return (0);
    }
	
    cmd = shell->current_cmd->args[0];
    func = find_builtin(cmd);
    if (func)
    {
        if (apply_redirections(shell->current_cmd) != 0) 
		{
            dup2(original_stdin, STDIN_FILENO);
            dup2(original_stdout, STDOUT_FILENO);
            close(original_stdin);
            close(original_stdout);
            shell->exit_status = 1; 
            return (1);
        }
        builtin_return_status = func(shell, shell->current_cmd->args);
        shell->exit_status = builtin_return_status;
        dup2(original_stdin, STDIN_FILENO);
        dup2(original_stdout, STDOUT_FILENO);
        close(original_stdin);
        close(original_stdout);
        return (1); 
    }
    close(original_stdin);
    close(original_stdout);
    return (0);
}
