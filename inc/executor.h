/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* executor.h                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2025/06/11 14:00:00 by marieli           #+#    #+#             */
/* Updated: 2025/06/11 14:00:00 by marieli          ###   ########.fr       */
/* */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

/*
 * -------------------------
 * Main Execution Functions
 * -------------------------
 */
void		ft_exec(t_shell *shell);
int			exec_external(t_shell *shell, char **args);
void		exec_pipeline(t_shell *shell, t_command *first_cmd);
void		exec_command(t_shell *shell, t_command *cmd, char *caller_cmd_path);

/*
 * -------------------------
 * Path & Redirection
 * -------------------------
 */
char		*find_executable(char *cmd, t_shell *shell);
int			apply_redirections(t_command *cmd);
int			process_heredoc(const char *delimiter);

/*
 * -------------------------
 * Execution Utilities
 * -------------------------
 */
char		*getenv_from_envp(char **envp, const char *name);
char		*join_path(const char *dir, const char *cmd);
void		free_split(char **arr);

/*
 * -------------------------
 * Piping Utilities from exec_pipe_utils.c
 * -------------------------
 */
void		setup_child_redirections(t_command *cmd, int p_fd, int p[2], int is_p);
void		exec_pipe_child(t_shell *shell, t_command *cmd, int p_fd, int p[2]);
void		handle_parent_fds(int pipefd[2], int *prev_fd, int is_pipe);
void		wait_for_children(t_shell *shell, pid_t last_pid);

#endif