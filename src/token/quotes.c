/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:15:45 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parser.h"

/*
 * @brief Extracts a quoted substring from the input.
 * Returns a NEWLY ALLOCATED string.
 * @param saveptr Pointer to the tokenizer state. Points to the char *after* the opening quote upon entry.
 * @param quote_char Type of quote.
 * @return Pointer to newly allocated extracted quoted string, or NULL if memory allocation fails or unmatched quote.
 * The caller is responsible for freeing the returned string.
 */
// src/quotes/quotes.c
// char *extract_quoted(char **saveptr, char quote_char)
// {
//     char *start_content;
//     char *end_content;
//     char *extracted_copy;
//     size_t len;

//     // (*saveptr)++; 
//     start_content = *saveptr; 
//     end_content = start_content;
//     while (*end_content)
//     {
//         if (*end_content == '\\' && (*(end_content + 1) == quote_char))
//         {
//             end_content += 2;
//             continue;
//         }
//         if (*end_content == quote_char)
//             break;
//         end_content++;
//     }
//     if (*end_content == '\0')
//     {
//         ft_putendl_fd("minishell: error: unmatched quote", STDERR_FILENO);
//         *saveptr = NULL;
//         return (NULL);
//     }
//     len = end_content - start_content; // Length is now correctly calculated for content only
//     extracted_copy = ft_strndup(start_content, len); // Duplicates content only
//     if (!extracted_copy)
//     {
//         perror("minishell: ft_strndup failed");
//         *saveptr = NULL;
//         return (NULL);
//     }
//     *saveptr = end_content + 1;
//     return(extracted_copy);
// }

char *extract_quoted(char **saveptr, char quote_char)
{
    char *start_content;
    char *end_content;
    char *extracted_copy;
    size_t len;

    (*saveptr)++;
    start_content = *saveptr; 
    end_content = start_content;
    while (*end_content)
    {
        if (*end_content == '\\' && (*(end_content + 1) == quote_char))
        {
            end_content += 2; 
            continue;
        }
        if (*end_content == quote_char) 
            break;
        end_content++;
    }
    if (*end_content == '\0')
    {
        ft_putendl_fd("minishell: error: unmatched quote", STDERR_FILENO);
        *saveptr = NULL;
        return (NULL);
    }

    len = end_content - start_content; // Length is now correctly calculated for content only
    extracted_copy = ft_strndup(start_content, len); // Duplicates content only
    if (!extracted_copy)
    {
        perror("minishell: ft_strndup failed");
        *saveptr = NULL; // Signal allocation error
        return (NULL);
    }

    *saveptr = end_content + 1; // Move saveptr past the closing quote
    return(extracted_copy);
}

t_token *handle_quotes(char **saveptr, char quote_char, t_shell *shell)
{
    char *start;
    char *expanded;
    t_token *new_token;

    if (!saveptr || !*saveptr || **saveptr != quote_char)
        return (NULL);
    start = extract_quoted(saveptr, quote_char);
    if (!start)
        return (NULL);

    if (quote_char == '"')
    {
        expanded = expand_variables(start, shell->envp, shell->exit_status); // Pass envp and exit_status
        if (!expanded)
        {
            p("Error: Memory allocation failed during variable expansion.\n");
            return (NULL);
        }
        new_token = create_token(expanded, TOKEN_WORD); // Double quoted result is a word
    }
    else // quote_char == '\''
        new_token = create_token(start, TOKEN_SINGLE_QUOTED);
    return (new_token);
}
