/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 23:03:48 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/14 23:03:48 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minishell.h"

// assuming that t_token and t_token_type was defined in minishell.h

/*
* @brief represents a redirection tied to a command
*/
typedef struct s_redirect
{
    t_token_type type;  /*type REDIR_IN, REDIR_OUT...*/
    char *filename; /*target filename or limiter for redirection*/
    struct s_redirect *next; /*pointer to the next redirection in the list*/
} t_redirect;

/*
* @brief represents a parsed shell command w args and redirections
*/
typedef struct s_command
{
    char *cmd;               /*main command like echo, ls...*/
    char **args;             /*NULL-terminated arr of args including cmd*/
    t_redirect *redirs;      /*linked list of redir associated w this command*/
    struct s_command *next;  /*pointer to the next command in sequence*/
    int is_pipe;             /*1 if connected via pipe, 0 if separated by semicolon */
} t_command;

#endif