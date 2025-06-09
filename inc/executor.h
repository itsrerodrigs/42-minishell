#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

int process_heredoc(const char *delimiter);
int 		apply_redirections(t_command *cmd);
void 		exec_pipeline(t_shell *shell, t_command *first_cmd);
int 		exec_external(t_shell *shell, char **args);
void 		ft_exec(t_shell *shell);
void		handle_cmd_not_found(t_shell *shell, char *cmd);
char 		*getenv_from_envp(char **envp, const char *name);
char 		*find_executable(char *cmd, t_shell *shell);
void 		free_split(char **arr);
char 		*join_path(const char *dir, const char *cmd);
void 		child_exec(char *cmd_path, char **args, t_command *cmd, char **envp);
void 		exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path);

#endif
