#include "../include/minishell.h"

int ft_exit(char **args)
{
    (void)args;
    p(RED "Shutting down...\n" RST);
    fflush(stdout);
    usleep(421337);
    exit(EXIT_SUCCESS);
}

int ft_env(char **args)
{
    extern char **environ;
    int i;

    (void)args;
    if (!environ)
        return(1);
    while (environ[i])
    {
        p("%s\n", environ[i]);
        i++;
    }
    return(0);
}