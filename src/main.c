#include "../inc/minishell.h"


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
		p(G "Looping through REPL...\n" RST); // Debug message
		args = get_tokens(line); //aqui é onde acontece a tokenização
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
