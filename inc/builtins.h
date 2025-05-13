
#ifndef STRUCTS_H
# define STRUCTS_H

// Declaração antecipada de t_shell
typedef struct s_shell t_shell;

typedef int (*builtin_func)(t_shell *, char **);

typedef struct s_builtin {
    char *name;
    builtin_func func;
} t_builtin;

#endif
