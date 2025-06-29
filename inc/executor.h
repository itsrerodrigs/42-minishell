/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 10:55:27 by marieli           #+#    #+#             */
/*   Updated: 2025/06/13 16:59:13 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/* Main Execution Functionn */
void		ft_exec(t_shell *shell);
int			exec_external(t_shell *shell, char **args);
void		exec_pipeline(t_shell *shell, t_command *first_cmd);
void		exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path);

/* Path & Redirection */
char		*find_executable(char *cmd, t_shell *shell);
int			apply_redirections(t_command *cmd);
// int			process_heredoc(const char *delimiter);
int			process_heredoc(t_redirect *redir, t_shell *shell);

/* Execution Utilities */
char		*getenv_from_envp(char **envp, const char *name);
char		*join_path(const char *dir, const char *cmd);
void		free_split(char **arr);
void		late_expand_exit_status(t_command *cmd, t_shell *shell);

/* Piping Utilities from exec_pipe_utils.c  */
void		setup_child_redirections(t_command *cmd, int p_fd,
				int p[2], int is_p);
void		exec_pipe_child(t_shell *shell, t_command *cmd, int p_fd,
				int p[2]);
void		handle_parent_fds(int pipefd[2], int *prev_fd, int is_pipe);
void		wait_for_children(t_shell *shell, pid_t last_pid);
void		s_save_fds_for_builtin(int *saved_stdin, int *saved_stdout);
void		s_restore_and_close_fds(int saved_stdin, int saved_stdout);
int			s_execute_and_set_status(t_shell *shell, t_command *cmd);
int			s_handle_pipe_creation(int *p, int is_pipe);
int			s_handle_fork_failure(int *p);

#endif
