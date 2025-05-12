#include <stdio.h>
#include <stdlib.h>
#include "../inc/minishell.h"

int exec_builtin(t_shell *shell); // Protótipos

int main(int argc, char **argv)
{
    t_shell shell;
    if (argc > 1)
    {
        shell.current_cmd = malloc(sizeof(t_cmd));
        shell.current_cmd->args = &argv[1];
    
        exec_builtin(&shell);
    
        free(shell.current_cmd);
    }
        return (0);
}
