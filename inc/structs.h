
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_builtin
{
    const char  *builtin_name;
    int         (*foo)(char **);
} t_builtin;

#endif
