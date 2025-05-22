
#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

// Declaração antecipada de t_shell
typedef struct s_shell t_shell;

typedef int (*builtin_func)(t_shell *, char **);

typedef struct s_builtin {
    char *name;
    builtin_func func;
} t_builtin;


typedef struct s_shell {
    t_cmd *current_cmd; 
    char **envp; /* cópia do ambiente do sistema que manipula export e unset */
    int exit_status; /* ultimo estatus de saída do shell */
} t_shell;


/*execução dos comandos*/
void ft_exec(t_shell *shell);



#endif
