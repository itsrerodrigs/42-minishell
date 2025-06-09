/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:12:34 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 14:07:54 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parser.h"
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
    t_token *token;
    t_token *next;

    token = *token_ptr;
    next = token->next;

    if (!next || next->type != TOKEN_WORD)
        return syntax_error(token->value);
    if (token->type == TOKEN_REDIR_IN)
        add_redir(cmd, REDIR_IN, next->value);
    else if (token->type == TOKEN_REDIR_OUT)
        add_redir(cmd, REDIR_OUT, next->value);
    else if (token->type == TOKEN_APPEND)
        add_redir(cmd, REDIR_APPEND, next->value);
    else if (token->type == TOKEN_HEREDOC)
        add_redir(cmd, REDIR_HEREDOC, next->value);

    *token_ptr = token->next->next;
    return (1);
}

/*
* @brief parses a list of lexical tokens into a linked list of commmand structure
* convert the array of tokens into a structured format
* handles tokens such aas words, quotes, pipes, redir, semicolons
* @return a linked list of parsed command structures (t_command)
*/
int handle_special_tokens(t_command **current, t_token **tokens)
{
    if ((*tokens)->type == TOKEN_PIPE)
    {
        if (!(*tokens)->next || (*tokens)->next->type == TOKEN_PIPE)
            return syntax_error("|");
        (*current)->is_pipe = 1;
        *current = new_command(*current);
    }
    else if ((*tokens)->type == TOKEN_SEMICOLON)
    {
        if (!(*tokens)->next || (*tokens)->next->type == TOKEN_SEMICOLON)
            return syntax_error(";");
        *current = new_command(*current);
    }
    return 0;
}

static int s_handle_word_token(t_command *current_cmd, t_token *token, t_shell *shell)
{
    char *equals_pos;
    int is_valid_name;
    char *c;

    equals_pos = ft_strchr(token->value, '='); 
    if (equals_pos && equals_pos != token->value && (ft_isalpha(token->value[0]) || token->value[0] == '_')) 
    {
        is_valid_name = 1; 
        for (c = token->value; c < equals_pos; ++c) 
        {
            if (!ft_isalnum(*c) && *c != '_') 
            { 
                is_valid_name = 0;
                break;
            }
        }
        if (is_valid_name) 
        {
            add_or_update_env(&shell->envp, token->value);
            return (1);
        }
    }
    return (handle_cmd_or_arg(current_cmd, token));
}


// t_command *parse_tokens(t_token *tokens, t_shell *shell)
// {
//     t_command *cmd_list;
//     t_command *current;
//     int error;

//     expand_token_list(tokens, shell);
//     cmd_list = init_command();
//     if (!cmd_list)
//         return (NULL);
//     current = cmd_list;
//     while (tokens != NULL && tokens->type != TOKEN_EOF)
//     {
//         if (is_token_cmd(tokens))
//         {
//             if (!handle_cmd_or_arg(current, tokens))
//                 return (NULL);
//         }
//         else if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_SEMICOLON)
//         {
//             error = handle_special_tokens(&current, &tokens);
//             if (error != 0)
//                 return (NULL);
//         }
//         else if (is_token_redir(tokens))
//         {
//             if (!tokens->next || tokens->next->type != TOKEN_WORD)
//                 return syntax_error("newline"), NULL;
//             if (!parse_redir(current, &tokens))
//                 return (NULL);
//             continue;
//         }
//         else
//             return syntax_error(tokens->value), NULL;
//         tokens = tokens->next;
//     }
//     return (cmd_list);
// }

t_command *parse_tokens(t_token *tokens, t_shell *shell) 
{
    t_command *cmd_list;
    t_command *current;
    int error;

    expand_token_list(tokens, shell);
    cmd_list = init_command();
    if (!cmd_list)
        return (NULL);
    current = cmd_list;
    while (tokens != NULL && tokens->type != TOKEN_EOF) 
    {
        if (is_token_cmd(tokens)) 
        { 
            if (!s_handle_word_token(current, tokens, shell))
                return (NULL);
            tokens = tokens->next; 
        }
        else if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_SEMICOLON) {
            error = handle_special_tokens(&current, &tokens);
            if (error != 0) return (NULL);
            tokens = tokens->next;
        }
        else if (is_token_redir(tokens)) 
        {
            if (!tokens->next || tokens->next->type != TOKEN_WORD)
                return syntax_error("newline"), NULL;
            if (!parse_redir(current, &tokens))
                return (NULL);
            //tokens = tokens->next;
        }
        else 
            return syntax_error(tokens->value), NULL;
        //tokens = tokens->next;
    }
    return (cmd_list);
}
