/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:12:22 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 15:13:43 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets signal handlers for the child process during heredoc input.
 */
static void	set_child_heredoc_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief The child process logic for reading heredoc input until a delimiter.
 */
static void	child_heredoc_logic(int pipe_write_fd, const char *delimiter)
{
	char	*line;

	set_child_heredoc_sig();
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_write_fd);
		ft_putstr_fd("\n", pipe_write_fd);
		free(line);
	}
	close(pipe_write_fd);
	exit(EXIT_SUCCESS);
}

/**
 * @brief Manages forking and waiting for the heredoc child process.
 */
static int	parent_heredoc_logic(pid_t pid, int pipe_fds[2])
{
	int	status;

	close(pipe_fds[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fds[0]);
		return (-1);
	}
	return (pipe_fds[0]);
}

/**
 * @brief Creates a pipe and forks to read heredoc input from the user.
 */
int	process_heredoc(const char *delimiter)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe for heredoc failed");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork for heredoc failed");
		close(pipe_fds[0]);
		close(pipe_fds[1]);
		return (-1);
	}
	else if (pid == 0)
	{
		close(pipe_fds[0]);
		child_heredoc_logic(pipe_fds[1], delimiter);
	}
	else
		return (parent_heredoc_logic(pid, pipe_fds));
	return (-1);
}
