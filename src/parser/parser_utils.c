/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:04:57 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/21 16:04:57 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include <stdlib.h>

/*
* @brief initialize a new command structure
*/
t_command *init_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        return (NULL);
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    cmd->is_pipe = 0;
    return (cmd);
     
}

/*
* @brief add an argument to the command's argument list
*/

int     add_arg(t_command *cmd, char *arg)
{
    char    **new_args;
    int     count;
    int     i;

    count = 0;
    if (cmd->args)
        while (cmd->args[count])
            count++;
    new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return (0);
    i = 0;
    while (i < count)
    {
        new_args[i] = cmd->args[i];
        i++;
    }
    new_args[i++] = arg;
    new_args[i] = NULL;
    free(cmd->args);
    cmd->args = new_args;
    return (1);
}

/*
* @brief add a new redirection to the cmds redir list
* @return 1 in case of success or 0 on failure
*/

int     add_redir(t_command *cmd, t_token_type type, char *filename)
{
    t_redirect *new_redir;
    t_redirect *last;

    new_redir = malloc(sizeof(t_redirect));
    if (!new_redir)
        return (0);
    new_redir->type = type;
    new_redir->filename = filename;
    new_redir->next = NULL;
    if (!cmd->redirs)
    {
        cmd->redirs = new_redir;
            return (1);
    }
    last = cmd->redirs;
    while (last->next)
        last = last->next;
    last->next = new_redir;
    return (1);
}

/*
* @brief handle a command or argument token
*/
int     handle_cmd_or_arg(t_command *cmd, t_token *token)
{
    if (!cmd->cmd)
        cmd->cmd = token->value;
    else
        return (add_arg(cmd, token->value));
    return (1);
}

/*
* @brief handle a direction token and its following filename token
* WORKING
*/
int handle_redir(t_command *cmd, t_token *token)
{
    if (!token || !token->next || !token->next->value)
        return 0;

    if (!add_redir(cmd, token->type, token->next->value))
        return 0;

    return 1;
}
