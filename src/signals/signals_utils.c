/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:53 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/09 10:49:28 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "\nSIGINT received.\n", 18); //debug
    display_prompt();
    fflush(stdout);
}
