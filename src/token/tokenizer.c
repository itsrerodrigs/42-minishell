/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* tokenizer.c                                        :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/04/24 18:29:00 by mmariano          #+#    #+#             */
/* Updated: 2025/06/11 10:25:00 by marieli          ###   ########.fr       */
/* */
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

    if (!segment)
        return (1);
    current_len = ft_strlen(*token_builder_ptr);
    segment_len = ft_strlen(segment);
    new_total_size = current_len + segment_len + 1;
    reallocated_builder = ft_realloc(*token_builder_ptr, new_total_size);
    if (!reallocated_builder)
    {
        free(segment);
        return (0);
    }
    *token_builder_ptr = reallocated_builder;
    ft_strlcat(*token_builder_ptr, segment, new_total_size);
    free(segment);
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
    char    quote_char;
    char    *quoted_content;
    char    *temp_saveptr_for_quote;

    quote_char = **current_pos_ptr;
    temp_saveptr_for_quote = *current_pos_ptr;
    quoted_content = extract_quoted(&temp_saveptr_for_quote, quote_char);
    if (!quoted_content)
        return (0);
    if (!s_append_to_builder(token_builder_ptr, quoted_content))
        return (0);
    *current_pos_ptr = temp_saveptr_for_quote;
    return (1);
}

static int is_token_operator(char c)
{
    return (c == '|' || c == '<' || c == '>');
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
    char *start_of_segment;
    char *segment_end;
    char *unquoted_part;

    start_of_segment = *current_pos_ptr;
    segment_end = *current_pos_ptr;
    while (*segment_end && !ft_strchr(delim, *segment_end) &&
        *segment_end != '\'' && *segment_end != '"' &&
        !is_token_operator(*segment_end))
    {
        segment_end++;
    }
    if (segment_end > start_of_segment)
    {
        unquoted_part = ft_strndup(start_of_segment, segment_end - start_of_segment);
        if (!unquoted_part)
        {
            perror("minishell: ft_strndup failed");
            return (0);
        }
        if (!s_append_to_builder(token_builder_ptr, unquoted_part))
            return (0);
    }
    *current_pos_ptr = segment_end;
    return (1);
}

char *extract_next_token(char **saveptr, const char *delim)
{
    char *token_builder;
    char *current_pos;

    if (!saveptr || !*saveptr || !delim)
        return (NULL);
    token_builder = ft_strdup("");
    if (!token_builder)
    {
        perror("minishell: ft_strdup failed");
        *saveptr = NULL;
        return (NULL);
    }
    current_pos = *saveptr;
    while (*current_pos)
    {
        if (*current_pos == '\'' || *current_pos == '"')
        {
            if (!s_process_quoted_segment(&token_builder, &current_pos))
            {
                free(token_builder);
                *saveptr = NULL;
                return (NULL);
            }
        }
        else if (ft_strchr(delim, *current_pos) || is_token_operator(*current_pos))
            break;
        else
        {
            if (!s_process_unquoted_segment(&token_builder, &current_pos, delim))
            {
                free(token_builder);
                *saveptr = NULL;
                return (NULL);
            }
        }
    }
    *saveptr = current_pos;
    if (*token_builder == '\0')
    {
        free(token_builder);
        return (NULL);
    }
    return (token_builder);
}

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
    if (ft_strncmp(op_start, ">>", 2) == 0)
    {
        type = TOKEN_APPEND;
        len = 2;
    }
    else if (ft_strncmp(op_start, "<<", 2) == 0)
    {
        type = TOKEN_HEREDOC;
        len = 2;
    }
    else if (*op_start == '|')
    {
        type = TOKEN_PIPE;
        len = 1;
    }
    else if (*op_start == '<')
    {
        type = TOKEN_REDIR_IN;
        len = 1;
    }
    else if (*op_start == '>')
    {
        type = TOKEN_REDIR_OUT;
        len = 1;
    }
    else
        return (NULL);
    char *op_value = ft_strndup(op_start, len);
    if (!op_value)
        return (NULL);
    *saveptr += len;
    return (create_token(op_value, type));
}

t_token *ft_get_next_token(char *str, const char *delim, char **saveptr, t_shell *shell)
{
    t_token     *new_token;
    char        *token_str_value;
    char        quote_char;
    const char  *whitespace_delim;

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
    new_token = create_token_with_fd(token_str_value, TOKEN_WORD, -1);
    return (new_token);
}