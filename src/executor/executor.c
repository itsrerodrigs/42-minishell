<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/09 14:49:38 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include "../inc/minishell.h"

/*
 * @brief Executes the current command from the shell state.
 * @param shell: Pointer to the shell structure containing the current command.
 * @return void.
 * @note This function first checks if the command is built-in by calling
 *       exec_builtin; if so, it returns immediately. Otherwise, it prints an error
 *       message indicating that the command is not found. External command handling
 *       (fork/execve) is yet to be implemented.
 */
void ft_exec(t_shell *shell)
{
    char **args;

    if (!shell || !shell->current_cmd)
        return;

    args = shell->current_cmd->args;
    if (!args || !args[0])
        return;

    /* Check if the command is a built-in.*/
/*     if (exec_builtin(shell))
        return; */

    /* TODO: Implement external command handling (fork + execve) */
    p(RED "Command not found: %s\n" RST, args[0]);
}
=======
    /* ************************************************************************** */
    /*                                                                            */
    /*                                                        :::      ::::::::   */
    /*   executor.c                                         :+:      :+:    :+:   */
    /*                                                    +:+ +:+         +:+     */
    /*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
    /*                                                +#+#+#+#+#+   +#+           */
    /*   Created: 2025/04/24 18:29:41 by mmariano          #+#    #+#             */
    /*   Updated: 2025/05/02 14:56:16 by renrodri         ###   ########.fr       */
    /*                                                                            */
    /* ************************************************************************** */

    #include "../inc/minishell.h"

    void	ft_exec(t_shell *shell)
{
	char	**args;

	if (!shell || !shell->current_cmd)
		return;

	args = shell->current_cmd->args;
	if (!args || !args[0])
		return;

	// Check if it's a builtin
	if (exec_builtin(shell))
		return;

	// TODO: Implement external command handling (fork + execve)
	p(RED "Command not found: %s\n" RST, args[0]);
}





    /*
    remove the global variables as soon as possible
    */

    /*
    t_builtin g_builtin[] = 
    {
    //	{.builtin_name="echo", .foo=shell_echo},
    //	{.builtin_name="env", .foo=shell_env},
        {.builtin_name="exit", .foo=ft_exit},
        {.builtin_name= NULL},
    };*/

    //t status = 0;

    //my comand is a builtin? -> call it directly
    //if not, call execvp: fork+execvp+wait

    /*void    ft_exec(char **args)
    {
        int     i;
        //int     status;
        const char *curr;

        if (args == NULL || args[0] == NULL)
            return;

        i = 0;
        while ((curr = t_builtin[i].builtin_name) != NULL)
        {
            if (!ft_strncmp(curr, args[0], ft_strlen(curr)))
            {
                status = t_builtin[i].foo(args);
                return;
            }
            ++i;
        }
        p(RED "Command not found: %s\n" RST, args[0]); // Debug or error message
    }*/


    // void ft_launch(char **args)
    // {
    // 	if (ft_fork() == CELL_Jr)
    // 		ft_execvp(args[0], args);
    // 	else
    // 		ft_wait(&status);

    // }
>>>>>>> builtins-test
