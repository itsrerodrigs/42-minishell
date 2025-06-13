/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:49:10 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/13 19:37:53 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include "tokens.h"
# include "parser.h"

typedef struct s_shell
{
	t_command	*current_cmd;
	pid_t		shell_pgid;
	char		**envp;
	int			exit_status;
	int			shell_is_interactive;
	int			shell_terminal_fd;
	bool		should_exit;
}	t_shell;

typedef int(*t_builtin_func)(t_shell *shell, char **args);

typedef struct s_builtin
{
	builtin_func	func;
	char			*name;
}	t_builtin;

/* Builtin Command Functions */
int	builtin_cd(t_shell *shell, char **args);
int	builtin_echo(t_shell *shell, char **args);
int	builtin_env(t_shell *shell, char **args);
int	builtin_exit(t_shell *shell, char **args);
int	builtin_unset(t_shell *shell, char **args);
int	builtin_pwd(t_shell *shell, char **args);
int	builtin_export(t_shell *shell, char **args);

/* Builtin Execution */
bool			is_builtin_parent_executable(t_command *cmd);
builtin_func		find_builtin(char *cmd);
int	exec_builtin(t_shell *shell);

/* Environment Variable Utils */
int	add_or_update_env(char ***envp, const char *var);
int	is_valid_env_name(const char *name, size_t name_len);
int	try_update_existing_var(char ***envp_ptr, const char *var,
		size_t key_len, int var_has_value);
int	add_new_env_entry(char ***envp_ptr, const char *var, int i);
void		free_envp(char **envp);
char		**dup_envp(char **envp);
char		*get_env_value(char **envp, const char *key);

/* CD Builtin Utilities */
void		update_pwd_vars(t_shell *shell, char *oldpwd);
char		*get_cd_path(t_shell *shell, char **args);

/* exit utils */
int		is_valid_exit_arg(const char *str);
void	handle_non_numeric_exit_arg(const char *arg);

#endif
