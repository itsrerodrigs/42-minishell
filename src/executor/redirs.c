/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:49:31 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/09 17:11:26 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

/*
 * @brief Opens a file for input redirection.
 */
static int apply_input_redir(char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/* 
 * @brief Opens a file for output redirection (overwrite).
 */
static int apply_output_redir(char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}


/*
 * @brief Opens a file for output redirection (append).
 */
static int apply_append_redir(char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (perror(filename), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

/*
 * @brief Handles a heredoc redirection.
 */
static int apply_heredoc_redir(t_redirect *redir)
{
	if (heredoc_fd == -1)
	{
		ftprint(stderr, "heredoc error: invalid file descriptor.");
		return (1);
	}
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 error (heredoc STDIN)");
		close(heredoc_fd);
		return (1);
	}
	close (heredoc_fd);
	return (0);
}

/*
 * @brief Applies all redirections for a command.
 */
int apply_redirections(t_command *cmd)
{
	t_redirect *redir = cmd->redirs;

	while (redir)
	{
		if (redir->type == REDIR_IN && apply_input_redir(redir->filename))
			return (1);
		if (redir->type == REDIR_OUT && apply_output_redir(redir->filename))
			return (1);
		if (redir->type == REDIR_APPEND && apply_append_redir(redir->filename))
			return (1);
		if (redir->type == REDIR_HEREDOC && apply_heredoc_redir(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
