/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:49:10 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 10:27:10 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokens.h"
#include "parser.h"

#ifndef BUILTINS_H
#define BUILTINS_H

typedef struct s_shell 
{
        t_command *current_cmd; 
        char **envp;
        int exit_status;
        pid_t shell_pgid;
        int shell_is_interactive;
        int shell_terminal_fd;
}       t_shell;

typedef int (*builtin_func)(t_shell *shell, char **args);

typedef struct s_builtin 
{
        char *name;
        builtin_func func;
}       t_builtin;

/* builtins funcionts*/
char            *get_cd_path(t_shell *shell, char **args);
void            update_pwd_vars(t_shell *shell, char *oldpwd);
char            **dup_envp(char **envp);
void            free_envp(char **envp);
char            *get_env_value(char **envp, const char *key);
int             exec_builtin(t_shell *shell);
int             builtin_cd(t_shell *shell, char **args);
int             builtin_echo(t_shell *shell, char **args);
int             builtin_env(t_shell *shell, char **args);
int             builtin_exit(t_shell *shell, char **args);
int             builtin_unset(t_shell *shell, char **args);
int             builtin_pwd(t_shell *shell, char **args);
builtin_func    find_builtin(char *cmd);
char            *get_cd_path_expanded(t_shell *shell, char **args);
bool            is_builtin_parent_executable(t_command *cmd);
int             is_valid_env_name(const char *name, size_t name_len);
int             try_update_existing_var(char ***envp_ptr, const char *var, size_t key_len, int var_has_value);
int             add_or_update_env(char ***envp, const char *var); 
int             builtin_export(t_shell *shell, char **args);

#endif
