/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:49:10 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/06 15:14:08 by mmariano         ###   ########.fr       */
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
char         *get_cd_path(t_shell *shell, char **args);
void         update_pwd_vars(t_shell *shell, char *oldpwd);
void         update_env_var(t_shell *shell, const char *key, const char *value);
int          ft_isdigit_str(const char *str);
char         **dup_envp(char **envp);
void         free_envp(char **envp);
char         *get_env_value(char **envp, const char *key);
int          exec_builtin(t_shell *shell);
int          builtin_cd(t_shell *shell, char **args);
int          builtin_echo(t_shell *shell, char **args);
int          builtin_env(t_shell *shell, char **args);
int          builtin_exit(t_shell *shell, char **args);
int          builtin_unset(t_shell *shell, char **args);
int          builtin_pwd(t_shell *shell, char **args);
int          builtin_printenv(t_shell *shell, char **args);
builtin_func find_builtin(char *cmd);
void	     add_or_update_env(char ***envp, const char *var);
char    *get_cd_path_expanded(t_shell *shell, char **args);
char    *save_and_get_oldpwd(void);
int     execute_chdir(const char *path);

#endif
