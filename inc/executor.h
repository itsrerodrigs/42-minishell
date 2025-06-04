#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "minishell.h"

typedef struct s_pipe_fd
{
    int pipe_fd[2];
    int prev_fd;
   // pid_t last_pid;
    int output_pipe;
} t_pipe_data;

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

void exec_pipeline(t_shell *shell, t_command *first_cmd);
void wait_pipeline_children(t_shell *shell, int last_executed_pid);

void child_exec(char *cmd_path, char **args, t_command *cmd, char **envp);
int validate_command(t_shell *shell);
void close_fd(int fd);
void handle_pipe_err(t_shell *shell, t_pipe_data *pdata);
pid_t    pipe_n_fork(t_pipe_data *pdata);
void setup_child_redirs(t_command *cmd, t_pipe_data *pdata);
void handle_pipe_parent(t_shell *shell, t_pipe_data *pdata, pid_t child_pid, int *last_executed_pid_ptr);



/*mari*/
void exec_command(t_shell *shell, t_command *cmd);

#endif
