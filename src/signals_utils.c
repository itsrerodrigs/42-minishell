#include "../../inc/minishell.h"

void sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    display_prompt();
    fflush(stdout);
}
