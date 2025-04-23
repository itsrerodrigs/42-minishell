#include "../../inc/minishell.h"

// void sigint_handler(int signum)
// {
//     (void)signum;
//     write(STDOUT_FILENO, "\nminishell> ", 12); //restart the prompt quando Ctrl+C
// }

void sigint_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "\nSIGINT received.\n", 18);
    display_prompt();
    fflush(stdout);
}
