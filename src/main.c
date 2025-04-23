#include "../include/minishell.h"


int main(int argc, char **argv)
{
	char			*line;
	char 			**args;
	unsigned int 	i;

	(void)argc;
    (void)argv;

	printbanner();

	line = ft_read_line();
	while (line != NULL)
	{
		//get tokens
		args = ft_split_line(line);
		i = 0;
		while (args && args[i])
		{
			//p("%s\n", args[i]); //escreve de volta no prompt
			ft_exec(args);
			i++;
		}
		i = 0;
		while (args && args[i])
        {
            free(args[i]); 
            i++;
        }
		free(line);
		free(args);
		line = ft_read_line();
		
	}
	return (EXIT_SUCCESS);
}
