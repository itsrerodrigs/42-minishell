#include "../include/minishell.h""

/*
ft_read_line:
		-display a command prompt: Encouraging the user to type a command.
		-read input from stdin: Collecting the user's input via the getline function.
		     -check if it is in interactive mode with isatty, the display the minishel prompt if needed
			 -In non-interactive mode (pipes or scripts), no prompt is displayed
		-returning a String: The function processes user input as a single string for further handling.
*/

static char *trim_whitespace(char *str)
{
    char *end;

    while (*str && isspace((unsigned char)*str))//trocar por libft
        str++;
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        *end-- = '\0';
    return(str);
}

static void display_prompt(void)
{
    char cwd[BUFSIZ];

    if (isatty(fileno(stdin))) //check if in interactive mode (terminal input)
    {
        ft_getcwd(cwd, sizeof(cwd)); //get the working dir
        p("%s%s minishell> %s", G, cwd, RST); //show prompt
    }
}

static char *validate_input_length(char *buf)
{
    if (strlen(buf) > 1024)
    {
        p(RED "Error: Input exceeds length limit (1024 chars).\n" RST);
        free(buf);
        return (NULL);
    }
    return buf;
}

char *ft_read_line(void)
{
    char    *buf;
    size_t  bufsize;

    buf = (NULL);
    bufsize = 0;
    
    display_prompt();

    if (getline(&buf, &bufsize, stdin) == -1) //read the input
    {   
        free(buf);
        if (feof(stdin))
            p(RED "[EOF]: Exiting minishell.\n" RST);
        else
            p(RED "Error: failed to read input.\n" RST);
        return (NULL);
    }
    buf = trim_whitespace(buf);
    buf = validate_input_length(buf);
    return (buf);
}

