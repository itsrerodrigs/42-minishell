/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:29:00 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/14 22:46:38 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokens.h"
#include "../inc/parser.h"


/*
 * @brief Appends a dynamically allocated segment to a dynamically built token string.
 * It takes ownership of `segment` (will free it).
 * @param token_builder_ptr Pointer to the current dynamically allocated token string.
 * @param segment The new segment to append (must be dynamically allocated, will be freed).
 * @return 1 on success, 0 on memory allocation failure.
 */
static int s_append_to_builder(char **token_builder_ptr, char *segment)
{
    size_t  current_len;
    size_t  segment_len;
    size_t  new_total_size;
    char    *reallocated_builder;

    if (!segment) // Nothing to append
        return (1);
    
    current_len = ft_strlen(*token_builder_ptr);
    segment_len = ft_strlen(segment);
    new_total_size = current_len + segment_len + 1; // +1 for null terminator

    reallocated_builder = ft_realloc(*token_builder_ptr, new_total_size);
    if (!reallocated_builder)
    {
        free(segment); // Free the segment we were trying to append
        return (0);
    }
    
    *token_builder_ptr = reallocated_builder; // Update the pointer to the newly sized block

    // Append the segment. ft_strlcat is safer as it prevents buffer overflows.
    ft_strlcat(*token_builder_ptr, segment, new_total_size);

    free(segment); // Free the segment after appending

    return (1);
}

/*
 * @brief Processes a quoted segment within a word token.
 * Extracts content from quotes, appends it to the builder, and updates position.
 * @param token_builder_ptr Pointer to the current dynamically allocated token string.
 * @param current_pos_ptr Pointer to the current position in the input string.
 * @return 1 on success, 0 on error (unmatched quote or allocation failure).
 */
static int s_process_quoted_segment(char **token_builder_ptr, char **current_pos_ptr)
{
    char quote_char;
    char *quoted_content_from_extractor;
    char *temp_saveptr_for_quote;
    char *content_without_quotes;
    size_t content_len_with_quotes;

    quote_char = **current_pos_ptr; 
    temp_saveptr_for_quote = *current_pos_ptr;
    quoted_content_from_extractor = extract_quoted(&temp_saveptr_for_quote, quote_char);
    if (!quoted_content_from_extractor && temp_saveptr_for_quote == NULL) 
        return (0);
    content_len_with_quotes = ft_strlen(quoted_content_from_extractor);
    if (content_len_with_quotes >= 2) 
        content_without_quotes = ft_strndup(quoted_content_from_extractor + 1, content_len_with_quotes - 2);
    else 
        content_without_quotes = ft_strdup("");
    free(quoted_content_from_extractor);
    if (!content_without_quotes) 
    { 
        perror("minishell: ft_strdup failed"); 
        return (0); 
    }
    if (!s_append_to_builder(token_builder_ptr, content_without_quotes)) { return (0); } 
    *current_pos_ptr = temp_saveptr_for_quote; 
    return (1);
}

/*
 * @brief Processes an unquoted segment within a word token.
 * Appends characters until a quote or delimiter is found.
 * @param token_builder_ptr Pointer to the current dynamically allocated token string.
 * @param current_pos_ptr Pointer to the current position in the input string.
 * @param delim The delimiter string.
 * @return 1 on success, 0 on allocation failure.
 */
static int s_process_unquoted_segment(char **token_builder_ptr, char **current_pos_ptr, const char *delim)
{
    char *start_of_segment = *current_pos_ptr;
    char *segment_end = *current_pos_ptr;
    char *unquoted_part;

    while (*segment_end && !ft_strchr(delim, *segment_end) && *segment_end != '\'' && *segment_end != '"')
    {
        segment_end++;
    }

    // Extract this unquoted segment (if any characters were found)
    if (segment_end > start_of_segment)
    {
        unquoted_part = ft_strndup(start_of_segment, segment_end - start_of_segment);
        if (!unquoted_part) {
            perror("minishell: ft_strndup failed");
            return (0);
        }

        if (!s_append_to_builder(token_builder_ptr, unquoted_part)) // s_append_to_builder will free unquoted_part
        {
            return (0); // Allocation error
        }
    }
    *current_pos_ptr = segment_end; // Update current_pos
    return (1);
}

char *extract_next_token(char **saveptr, const char *delim)
{
    char *token_builder;
    char *current_pos;

    if (!saveptr || !*saveptr || !delim)
        return (NULL);

    token_builder = ft_strdup(""); // Initialize with empty string
    if (!token_builder) {
        perror("minishell: ft_strdup failed");
        *saveptr = NULL; // Signal allocation error
        return (NULL);
    }
    current_pos = *saveptr;

    while (*current_pos) //
    {
        if (*current_pos == '\'' || *current_pos == '"') //
        {
            if (!s_process_quoted_segment(&token_builder, &current_pos)) //
            {
                free(token_builder); 
                *saveptr = NULL; // Propagate unmatched quote or allocation error
                return (NULL); //
            }
        }
        else if (ft_strchr(delim, *current_pos)) //
        {
            break; // Delimiter found, end of token
        }
        else // Regular character
        {
            if (!s_process_unquoted_segment(&token_builder, &current_pos, delim)) //
            {
                free(token_builder);
                *saveptr = NULL; // Propagate allocation error
                return (NULL); //
            }
        }
    }

    *saveptr = current_pos; // Update saveptr to the end of this token

    if (*token_builder == '\0') // Token is empty (e.g., if only delimiters were found)
    {
        free(token_builder); //
        return (NULL); //
    }
    return (token_builder); // This string needs to be free'd by create_token
}

/*
 ** @brief: Handles quoted strings inside ft_strtok.
 ** @param saveptr: Pointer to the tokenizer state.
 ** @return: Extracted quoted string or NULL if an error occurs.
 */
// static t_token *handle_token_quotes(char **saveptr, t_shell *shell)
// {
//     char        quote_char;

//     if (!saveptr || !*saveptr)
//         return (NULL);
//     quote_char = **saveptr;
//     if (quote_char != '\'' && quote_char != '"')
//         return (NULL);
//     return (handle_quotes(saveptr, quote_char, shell));
// }

static void skip_delim(char **saveptr, const char *delim) 
{
    while (**saveptr && ft_strchr(delim, **saveptr))
        (*saveptr)++;
}



static t_token *s_extract_operator_token(char **saveptr)
{
    char    *op_start;
    size_t  len;
    t_token_type type;

    op_start = *saveptr;
    len = 0;

    // Check for multi-character operators first (e.g., >>, <<)
    if (ft_strncmp(op_start, ">>", 2) == 0) 
    {
        type = TOKEN_APPEND;
        len = 2;
    } else if (ft_strncmp(op_start, "<<", 2) == 0) 
    {
        type = TOKEN_HEREDOC;
        len = 2;
    }
    // Then single-character operators
    else if (*op_start == '|') 
    {
        type = TOKEN_PIPE;
        len = 1;
    } else if (*op_start == '<') 
    {
        type = TOKEN_REDIR_IN;
        len = 1;
    } else if (*op_start == '>') 
    {
        type = TOKEN_REDIR_OUT;
        len = 1;
    }
    else
        return (NULL);

    char *op_value = ft_strndup(op_start, len);
    if (!op_value)
        return (NULL); // Memory allocation failure

    *saveptr += len; // Advance saveptr past the consumed operator
    return (create_token(op_value, type)); // Use your existing create_token
}

t_token *ft_get_next_token(char *str, const char *delim, char **saveptr, t_shell *shell)
{
    t_token *new_token;
    char *token_str_value;
    char quote_char;
    const char *whitespace_delim;
    
    whitespace_delim = " \t\n"; 

    if (!saveptr || !delim) 
        return (NULL);
    if (str)
        *saveptr = str;
    skip_delim(saveptr, whitespace_delim); 

    if (**saveptr == '\0')
        return (NULL);
    new_token = s_extract_operator_token(saveptr);
    if (new_token) 
        return (new_token);
    quote_char = **saveptr;
    if (quote_char == '\'' || quote_char == '"')
    {
        new_token = handle_quotes(saveptr, quote_char, shell);
        if (new_token)
            return (new_token);
        return (NULL);
    }
    token_str_value = extract_next_token(saveptr, delim); 
    if (!token_str_value)
        return (NULL);

    new_token = create_token(token_str_value, get_token_type(token_str_value));
    return (new_token);
}
