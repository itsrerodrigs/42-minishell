#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

void ft_exec(t_shell *shell);
void handle_cmd_not_found(t_shell *shell, char *cmd);
void child_exec(char *cmd_path, char **args, t_command *cmd, char **envp);
void launch_process(t_shell *shell, t_command *cmd);
void exec_pipeline(t_shell *shell, t_command *first_cmd);
int exec_external(t_shell *shell, char **args);

char *getenv_from_envp(char **envp, const char *name);
char *ft_strjoin_path(char *s1, char *s2);
void free_split(char **arr);
char *find_executable(char *cmd, char **envp);
char *get_cmd_path(char *cmd, char **paths);

void exec_pipeline(t_shell *shell, t_command *first_cmd);




int apply_redirections(t_command *cmd);
int validate_command(t_shell *shell);

#endif
