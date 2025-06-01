/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:12:22 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/30 20:12:22 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

/*
* @brief Handle heredoc redirection (<<). Reads input until delimiter is found.
* @param redir The redirection structure containing the limiter.
* @return int Returns a file descriptor for the heredoc or -1 on error.
*/

int     handle_heredoc(t_redirect *redir)
{
    int pipefd[2];
    char *line;

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strncmp(line, redir->filename, ft_strlen(redir->filename) + 1 ) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, pipefd[1]);
        free(line);
    }
    close(pipefd[1]);
    return (pipefd[0]);
}