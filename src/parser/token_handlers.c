#include "../inc/minishell.h"

/*
implement actions for each token later
*/

char *handle_single_quotes(char **saveptr)
{
    char *start;

    start = ++(*saveptr); // Skip the opening single quote
    while (**saveptr && **saveptr != '\'') // Traverse until closing single quote
        (*saveptr)++;

    if (**saveptr == '\'') // If there's a closing single quote, terminate
    {
        **saveptr = '\0';
        (*saveptr)++;
    }
    else
    {
        printf("Error: Unclosed single quote.\n"); // Handle unclosed quotes gracefully
        return (NULL);
    }

    printf("Single Quote Token: [%s]\n", start); // Debug statement
    return (start); // Return the quoted token
}
char *merge_single_quotes(char *token, char **saveptr)
{
    size_t len;
    char *merged;
    char *next;

    merged = strdup(token);
    if (!merged)
        return NULL;
    /* Loop until the merged token ends with a single quote */
    while (merged[strlen(merged) - 1] != '\'')
    {
        next = ft_strtok(NULL, DELIM, saveptr);
        if (!next)
            break;
        len = strlen(merged) + strlen(next) + 2;  /* +1 for space, +1 for '\0' */
        merged = realloc(merged, len);
        if (!merged)
            return NULL;
        strcat(merged, " ");
        strcat(merged, next);
    }
    /* Remove the starting and ending quotes */
    if (merged[0] == '\'' && merged[strlen(merged) - 1] == '\'')
    {
        merged[strlen(merged) - 1] = '\0';
        char *result = strdup(merged + 1);
        free(merged);
        return result;
    }
    return merged;
}

char *handle_double_quotes(char **saveptr)
{
    char *start;

    start = ++(*saveptr); // Skip the opening double quote
    while (**saveptr && **saveptr != '"') // Traverse until closing double quote
        (*saveptr)++;

    if (**saveptr == '"') // Terminate at the closing quote
    {
        **saveptr = '\0';
        (*saveptr)++;
    }

    printf("Double Quote Token: [%s]\n", start); // Debug statement
    return (start); // Return the quoted token
}

char *merge_double_quotes(char *token, char **saveptr)
{
    size_t len;
    char *merged;
    char *next;

    merged = strdup(token);
    if (!merged)
        return NULL;
    while (merged[strlen(merged) - 1] != '"')
    {
        next = ft_strtok(NULL, DELIM, saveptr);
        if (!next)
            break;
        len = strlen(merged) + strlen(next) + 2;
        merged = realloc(merged, len);
        if (!merged)
            return NULL;
        strcat(merged, " ");
        strcat(merged, next);
    }
    if (merged[0] == '"' && merged[strlen(merged) - 1] == '"')
    {
        merged[strlen(merged) - 1] = '\0';
        char *result = strdup(merged + 1);
        free(merged);
        return result;
    }
    return merged;
}

char *handle_operators(char *token)
{
    return (token); // for |, >, < 
}
