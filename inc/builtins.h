/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:49:10 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/29 20:02:08 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parser.h"

#ifndef BUILTINS_H
#define BUILTINS_H

typedef struct s_shell {
    t_command *current_cmd; 
    char **envp; /* cópia do ambiente do sistema que manipula export e unset */
    int exit_status; /* ultimo estatus de saída do shell */
} t_shell;

typedef int (*builtin_func)(t_shell *shell, char **args);

typedef struct s_builtin {
    char *name;
    builtin_func func;
} t_builtin;

/* builtins funcionts*/
char    *get_cd_path(t_shell *shell, char **args);
void    update_pwd_vars(t_shell *shell, char *oldpwd);
void    update_env_var(t_shell *shell, const char *key, const char *value);
int ft_isdigit_str(const char *str);
char    **realloc_mem(char **ptr, size_t new_size);
char    *get_env_value(char **envp, const char *key);
int     exec_builtin(t_shell *shell);
int builtin_cd(t_shell *shell, char **args);
int builtin_echo(t_shell *shell, char **args);
int builtin_env(t_shell *shell, char **args);
int builtin_exit(t_shell *shell, char **args);
int builtin_unset(t_shell *shell, char **args);
int builtin_pwd(t_shell *shell, char **args);

#endif
