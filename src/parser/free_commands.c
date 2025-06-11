/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:31:37 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/21 23:31:37 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void free_redirs(t_redirect *redir)
{
    t_redirect *tmp;

    while (redir)
    {
        tmp = redir->next;
        if (redir->filename)
            free(redir->filename);
        free(redir);
        redir = tmp;
    }
}

void free_commands(t_command *cmd)
{
    t_command *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        //if (cmd->cmd)
        //    free(cmd->cmd);
        if (cmd->args)
        {
            free(cmd->args);
        }
        if (cmd->redirs)
            free_redirs(cmd->redirs);
        free(cmd);
        cmd = tmp;
    }
}

