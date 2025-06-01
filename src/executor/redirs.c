/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:49:31 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 14:49:31 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>  // open
#include <unistd.h> // dup2

static int apply_input_redir(t_redirect *redir)
{
	int fd = open(redir->filename, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int apply_output_redir(t_redirect *redir)
{
	int fd;

	if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else // REDIR_APPEND
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);

	if (fd < 0)
	{
		perror(redir->filename);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int apply_redirections(t_command *cmd)
{
	t_redirect *redir = cmd->redirs;

	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (apply_input_redir(redir))
				return (1);
		}
		else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		{
			if (apply_output_redir(redir))
				return (1);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			int heredoc_fd = handle_heredoc(redir);
			if (heredoc_fd < 0)
				return (1);
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		redir = redir->next;
	}
	return (0);
}
