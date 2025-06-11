/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:12:22 by renrodri          #+#    #+#             */
/*   Updated: 2025/06/11 10:24:55 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include <fcntl.h>


static void set_child_heredoc_sig(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}

static void child_heredoc_logic(int pipe_write_fd, const char *delimiter)
{
    char *line;
    
    set_child_heredoc_sig();
    close(pipe_write_fd);
    while(1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
        {
            free(line);
            break;
        }
        ft_putstr_fd(line, pipe_write_fd);
        ft_putstr_fd("\n", pipe_write_fd);
        free(line);
    }
    close(pipe_write_fd);
    exit(EXIT_SUCCESS);
}

int process_heredoc(const char *delimiter)
{
    int pipe_fds[2];
    pid_t pid;
    int status;

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
        child_heredoc_logic(pipe_fds[1], delimiter);
    }
    else
    {
        close(pipe_fds[1]);
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            close(pipe_fds[0]);
            return (-1);
        }
        return (pipe_fds[0]);
    }
    return (-1);
}

