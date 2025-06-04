#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

int handle_heredoc(t_redirect *redir);
int apply_redirections(t_command *cmd);
void exec_pipeline(t_shell *shell, t_command *first_cmd);
void launch_process(t_shell *shell, t_command *cmd);
int exec_external(t_shell *shell, char **args);
void ft_exec(t_shell *shell);
void handle_cmd_not_found(t_shell *shell, char *cmd);
char *getenv_from_envp(char **envp, const char *name);
char *find_executable(char *cmd, t_shell *shell);
char *get_cmd_path(char *cmd, char **paths);
char *ft_strjoin_path(char *s1, char *s2);
void free_split(char **arr);
char *join_path(const char *dir, const char *cmd);
char get_executable_path(char *cmd, t_shell *shell);

void child_exec(char *cmd_path, char **args, t_command *cmd, char **envp);
int validate_command(t_shell *shell);

/*mari*/
void exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path);

#endif
