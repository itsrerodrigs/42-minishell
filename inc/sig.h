/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:26:41 by mmariano          #+#    #+#             */
/*   Updated: 2025/06/02 18:04:47 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
#define SIG_H

#include "minishell.h"
#include <signal.h>

typedef struct s_old_signals
{
    struct sigaction int_sa;
    struct sigaction quit_sa;
}   t_old_signals;


void 	save_and_ignore_signals(struct sigaction *old_int, struct  sigaction *old_quit);
void 	restore_signals(struct sigaction *old_int, struct sigaction *old_quit);
void 	set_child_default_signals(void);
void 	setup_signal_handling(void);
void 	sigint_handler(int signum);

#endif