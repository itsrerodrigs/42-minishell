#include "../../inc/minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "\nSIGINT received.\n", 18); //debug
    display_prompt();
    fflush(stdout);
}
