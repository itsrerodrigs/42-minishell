#include "../inc/minishell.h"

void free_tokens(char **tokens)
{
    unsigned int i = 0;
    while (tokens && tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}

