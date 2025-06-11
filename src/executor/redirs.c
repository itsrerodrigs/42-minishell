/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:49:31 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:14:20 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Opens a file for input redirection and dups it to STDIN.
 */
static int	apply_input_redir(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 error (input STDIN)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Opens a file for output/append redirection and dups it to STDOUT.
 */
static int	apply_output_redir(char *filename, int oflag)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | oflag, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 error (output STDOUT)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Dups the heredoc pipe to STDIN.
 */
static int	apply_heredoc_redir(t_command *cmd)
{
	int	heredoc_fd;

	heredoc_fd = cmd->heredoc_pipe_read_fd;
	if (heredoc_fd == -1)
	{
		ft_putendl_fd("heredoc error: invalid file descriptor.", 2);
		return (1);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 error (heredoc STDIN)");
		close(heredoc_fd);
		return (1);
	}
	return (0);
}

/**
 * @brief Applies a single redirection based on its type.
 */
static int	apply_one_redir(t_redirect *redir, t_command *cmd)
{
	int	status;

	status = 0;
	if (redir->type == REDIR_IN)
		status = apply_input_redir(redir->filename);
	else if (redir->type == REDIR_OUT)
		status = apply_output_redir(redir->filename, O_TRUNC);
	else if (redir->type == REDIR_APPEND)
		status = apply_output_redir(redir->filename, O_APPEND);
	else if (redir->type == REDIR_HEREDOC)
		status = apply_heredoc_redir(cmd);
	return (status);
}

/**
 * @brief Applies all redirections for a given command.
 */
int	apply_redirections(t_command *cmd)
{
	t_redirect	*redir;
	int			status;

	redir = cmd->redirs;
	status = 0;
	while (redir)
	{
		status = apply_one_redir(redir, cmd);
		if (status != 0)
			return (status);
		redir = redir->next;
	}
	return (0);
}
