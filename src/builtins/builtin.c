#include "../inc/minishell.h"


int ft_exit(char **args)
{
    int exit_code;
    
    exit_code = EXIT_SUCCESS;

    if (args[1]) 
    {
        exit_code = ft_atoi(args[1]);
        if (exit_code < 0)
            exit_code = EXIT_FAILURE;
    }
    p(RED "Shutting down...\n" RST);
    fflush(stdout);
    usleep(421337);
    exit(exit_code);
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
