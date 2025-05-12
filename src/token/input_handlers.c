/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 18:28:18 by mmariano          #+#    #+#             */
/*   Updated: 2025/05/02 14:47:52 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void printbanner(void)
{
    p(C "Initializing Minishell.. \n" RST);
}

void display_prompt(void)
{
    char cwd[BUFSIZ];

    if (isatty(fileno(stdin))) 
    {
        ft_getcwd(cwd, sizeof(cwd)); /* get the working dir */
        p("%s%s minishell> %s", G, cwd, RST); /* show prompt */
    }
}

char *trim_whitespace(char *str)
{
    char *end;

    while (ft_isspace((unsigned char)*str))
        str++;
    if (*str == '\0')
        return (str);
    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';

    return (str);
}

char *read_input(void)
{
    char *buf;

    display_prompt();

    buf = readline(""); 
    if (!buf)
    {
        p(RED "[EOF]: Exiting minishell.\n" RST);
        return (NULL);
    }
    if (*buf)
        add_history(buf);
    /* trocar pelo builtin handler depois */
    if (ft_strncmp(buf, "exit", 4) == 0 && ft_strlen(buf) == 4)
    {
        char *args[] = {buf, NULL};
        ft_exit(args);
    }
    buf = trim_whitespace(buf);
    return (buf);
}