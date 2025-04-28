/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:18 by mmariano          #+#    #+#             */
/*   Updated: 2025/04/28 16:39:04 by mmariano         ###   ########.fr       */
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
        return (NULL);
    }
    return buf;
}

char *read_input(void)
{
    char *buf;

    display_prompt();

    buf = readline(""); 
    if (!buf)
    {
        printf(RED "[EOF]: Exiting minishell.\n" RST);
        return (NULL);
    }
    if (*buf)
        add_history(buf);
    if (ft_strncmp(buf, "exit", 4) == 0 && ft_strlen(buf) == 4)
    {
        char *args[] = {buf, NULL};
        ft_exit(args);
    }
    buf = trim_whitespace(buf);
    buf = validate_input_length(buf);
    return (buf);
}



