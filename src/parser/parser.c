/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:34 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/21 16:12:34 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <stdlib.h>

/*
* @brief creates a new command node and links it to the current cmd
*/

t_command *new_command(t_command *current)
{
    current->next = init_command();
    return (current->next);
}

/*
* @brief parses a list of tokens into a linked list of commands
*/

int parse_redir(t_command *cmd, t_token **token_ptr)
{
    t_token *token = *token_ptr;

    if (!handle_redir(cmd, token))
        return (0);

    if (!token->next)  // Verifica se o próximo token existe
        return (0);

    *token_ptr = token->next->next; // Avança dois nós: redir + filename
    return (1);
}

/*
* @brief parses a list of lexical tokens into a linked list of commmand structure
* convert the array of tokens into a structured format
* handles tokens such aas words, quotes, pipes, redir, semicolons
* @return a linked list of parsed command structures (t_command)
*/

t_command *parse_tokens(t_token *tokens)
{
    t_command *cmd_list;
    t_command *current;

    cmd_list = init_command();
    if (!cmd_list)
        return (NULL);
    current = cmd_list;

    while (tokens != NULL && tokens->type != TOKEN_EOF)
    {
        if (tokens->type == TOKEN_VALUE
        || tokens->type == TOKEN_SINGLE_QUOTED
        || tokens->type == TOKEN_DOUBLE_QUOTED)
        {
            if (!handle_cmd_or_arg(current, tokens))
                return (NULL);
        }
        else if (tokens->type == TOKEN_PIPE)
        {            
            current->is_pipe = 1;
            current = new_command(current);
            if (!current)
                return (NULL);
        }
        else if (tokens->type == TOKEN_REDIR_OUT
        || tokens->type == TOKEN_REDIR_IN
        || tokens->type == TOKEN_APPEND
        || tokens->type == TOKEN_HEREDOC)
        {
            if (!parse_redir(current, &tokens))
                return (NULL);
            continue;
        }
        else if (tokens->type == TOKEN_SEMICOLON)
        {
            current = new_command(current);
            if (!current)
                return (NULL);
        }
        tokens = tokens->next;
    }
    return (cmd_list);
}