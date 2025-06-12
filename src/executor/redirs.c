/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:49:31 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/12 13:42:31 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Opens a file for input redirection and dups it to the specified
 * source_fd.
 */
static int	apply_input_redir(int source_fd, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, source_fd) == -1)
	{
		perror("dup2 error (input)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Opens a file for output/append redirection and dups it to the
 * specified source_fd.
 */
static int	apply_output_redir(int source_fd, char *filename, int oflag)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | oflag, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, source_fd) == -1)
	{
		perror("dup2 error (output)");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

/**
 * @brief Dups the heredoc pipe to STDIN. This function is unchanged.
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
	if (redir->type == REDIR_IN)
		return (apply_input_redir(redir->source_fd, redir->filename));
	else if (redir->type == REDIR_OUT)
		return (apply_output_redir(redir->source_fd, redir->filename, O_TRUNC));
	else if (redir->type == REDIR_APPEND)
		return (apply_output_redir(redir->source_fd, redir->filename, O_APPEND));
	else if (redir->type == REDIR_HEREDOC)
		return (apply_heredoc_redir(cmd)); 
	return (0);
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