#include "../inc/minishell.h"

void free_tokens(char **tokens)
{
    unsigned int i = 0;
    if (!tokens)
        return;
    while (tokens[i])
        free(tokens[i++]);
    free(tokens);
}

