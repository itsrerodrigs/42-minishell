/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:43 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:58:19 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

// pid_t   ft_wait(int *status)
// {
//     pid_t   result;

//     if(!status)
//     {
//         fprintf(stderr, RED "Wait: status argument required\n" RST);
//         return(-1);
//     }
//     result = wait(status);
//     if (result == -1)
//         perror(RED "Wait failed\n" RST);
//     if (WIFEXITED(*status))
//         *status = WEXITSTATUS(*status);
//     return(result);
// }

// void    ft_execvp(const char *file, char *const argv[])
// {
//     if (!file || !argv)
//     {
//         fprintf(stderr, RED "Wxecvp: invalid arguments\n" RST);
//         exit(EXIT_FAILURE);
//     }
//     if (execvp(file, argv) == -1)
//     {
//         perror(RED "CELL_Jr failed\n" RST);
//         exit(EX_UNAVAILABLE);
//     }
// }

// pid_t   ft_fork(void)
// {
//     pid_t   pid;

//     pid = fork();
//     if (pid < 0)
//     {
//         perror(RED "Fork failed\n" RST);
//         exit(EX_OSERR);
//     }
//     return(pid);
// }




