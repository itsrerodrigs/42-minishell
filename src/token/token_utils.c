/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:48:50 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 19:55:37 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *create_token_with_fd(char *value, t_token_type type, int fd_val)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
    {
        free(value);
        return (NULL);
    }
    new_token->value = ft_strdup(value);
    if (!new_token->value) {
        free(new_token);
        free(value);
        return (NULL);
    }
    new_token->type = type;
    new_token->fd = fd_val;
    new_token->next = NULL;

    free(value);
    return (new_token);
}

// static t_token *s_extract_redir_token(char **saveptr)
// {
//     char    *op_start = *saveptr;
//     int     fd_val = -1;
//     t_token_type type;
//     char    *str_val;
//     size_t  len = 0;

//     char *num_start = op_start;
//     size_t num_digits = 0;
//     while (ft_isdigit(*op_start)) {
//         op_start++;
//         num_digits++;
//     }
//     if (num_digits > 0) {
//         fd_val = ft_atoi_n(num_start, num_digits); 
//     } else {
//         fd_val = -1; 
//     }
//     if (*op_start == '<') {
//         if (*(op_start + 1) == '<') 
//         {
//             type = TOKEN_HEREDOC;
//             len = 2;
//             if (fd_val == -1) fd_val = 0; 
//         }
//         else 
//         { 
//             type = TOKEN_REDIR_IN;
//             len = 1;
//             if (fd_val == -1) fd_val = 0; 
//         }
//     }
//     else if (*op_start == '>') 
//     {
//         if (*(op_start + 1) == '>') 
//         {
//             type = TOKEN_APPEND;
//             len = 2;
//             if (fd_val == -1) fd_val = 1;
//         } 
//         else 
//         {
//             type = TOKEN_REDIR_OUT;
//             len = 1;
//             if (fd_val == -1) fd_val = 1;
//         }
//     }
//     else if (*op_start == '|') 
//     {
//         type = TOKEN_PIPE;
//         len = 1;
//         fd_val = -1;
//     }
//     else {
//         if (num_digits > 0) {  
//             *saveptr = num_start;
//             return (NULL);
//         }
//         return (NULL);
//     }

//     str_val = ft_strndup(num_start, (op_start + len) - num_start);
//     if (!str_val)
//         return (NULL);

//     *saveptr = op_start + len;
//     return (create_token_with_fd(str_val, type, fd_val));
// }
