#include "../inc/minishell.h"

char *trim_whitespace(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;
    if (*str == '\0')
        return (str);
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';

    return (str);
}
int main(void)
{
    char *input;
    char **tokens;
    size_t bufsize;
    unsigned int token_count;
    char *local_saveptr = NULL; // Local saveptr initialized to NULL

    // Sample input string for testing
    input = ft_strdup("ls -l | grep \"test\"");
    //input = ft_strdup("echo \"hello world\"");
    if (!input)
    {
        p(RED "Error: strdup failed for input\n" RST);
        return (EXIT_FAILURE);
    }

    // Initialize token array
    tokens = initialize_token_array(&bufsize);
    if (!tokens)
    {
        p(RED "Error: Failed to allocate memory for token array in initialize_token_array\n" RST);
        free(input);
        return (EXIT_FAILURE);
    }

    // Tokenize the input
    token_count = extract_tokens(input, &tokens, &bufsize, &local_saveptr);
    if (token_count == 0)
    {
        p(RED "Error: No tokens found or error occurred in extract_tokens\n" RST);
        free(input);
        free_tokens(tokens);
        return (EXIT_FAILURE);
    }

    // Display the tokens
    printf("Tokens:\n");
    for (unsigned int i = 0; i < token_count; i++)
    {
        if (tokens[i])
            printf("[%u]: %s\n", i, tokens[i]);
        else
            p(RED "Error: Null token detected in main\n" RST);
    }

    // Clean up
    free(input);
    free_tokens(tokens);

    return (EXIT_SUCCESS);
}
