/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:18 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/24 18:28:19 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void display_prompt(void)
{
    char cwd[BUFSIZ];

    if (isatty(fileno(stdin))) 
    {
        ft_getcwd(cwd, sizeof(cwd)); //get the working dir
        p("%s%s minishell> %s", G, cwd, RST); //show prompt
    }
}

char *trim_whitespace(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;
    if (*str == '\0')
        return (str);
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';

    return (str);
}

static char *validate_input_length(char *buf)
{
    if (ft_strlen(buf) > 1024)
    {
        p(RED "Error: Input exceeds length limit (1024 chars).\n" RST);
        free(buf);
        return (NULL);
    }
    return buf;
}

char *read_input(void)
{
    char    *buf;
    size_t  bufsize;

    buf = (NULL);
    bufsize = 0;
    
    display_prompt();

    if (getline(&buf, &bufsize, stdin) == -1) //read the input
    {
        if (errno == EINTR) // Handle signal interruption
        {
            free(buf);
            return(NULL);
        }
        if (feof(stdin))
            p(RED "[EOF]: Exiting minishell.\n" RST);
        else
            p(RED "Error: failed to read input.\n" RST);
        return (NULL);
    }
    buf = trim_whitespace(buf);
    buf = validate_input_length(buf);
    free(buf);
    return (buf);
}

