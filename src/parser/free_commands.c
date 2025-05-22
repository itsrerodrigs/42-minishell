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
#include "test.h"

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

void free_commands_list(t_command *cmd)
{
    t_command *tmp;
    int i;

    while (cmd)
    {
        tmp = cmd->next;
        if (cmd->cmd)
            free(cmd->cmd);
        if (cmd->args)
        {
            for (i = 0; cmd->args[i]; i++)
                free(cmd->args[i]);
            free(cmd->args);
        }
        if (cmd->redirs)
            free_redirs(cmd->redirs);
        free(cmd);
        cmd = tmp;
    }
}

void free_tokens(t_token **tokens)
{
    t_token *cur;
    t_token *next;

    if (!tokens || !*tokens)
        return;
    cur = *tokens;
    while (cur)
    {
        next = cur->next;
        if (cur->value)
            free(cur->value);
        free(cur);
        cur = next;
    }
    *tokens = NULL;
}
