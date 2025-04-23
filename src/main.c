#include "../inc/minishell.h"

static void free_tokens(char **tokens)
{
    unsigned int i = 0;
    while (tokens && tokens[i])
    {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}


int main(int argc, char **argv)
{
	char			*line;
	char 			**args;

	(void)argc;
    (void)argv;

	signal(SIGINT, sigint_handler); //para Ctrl+C
	printbanner();
	
	line = read_input(); //lê o input
	while (line != NULL) //começa o REPL loop
	{
		args = split_line(line); //aqui é onde acontece a tokenização
		if (args)
		{
			ft_exec(args); //esa função vai lidar com a execução dos comandos
            free_tokens(args); //free tokens
			//p("%s\n", args[i]); //escreve de volta no prompt, deixei pra debugar
		}
		free(line);
		line = read_input();		
	}
	return (EXIT_SUCCESS);
}
