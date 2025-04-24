#include "../inc/minishell.h"

/*
remove the global variables as soon as possible
*/
t_builtin g_builtin[] = 
{
//	{.builtin_name="echo", .foo=shell_echo},
//	{.builtin_name="env", .foo=shell_env},
	{.builtin_name="exit", .foo=ft_exit},
	{.builtin_name= NULL},
};

int status = 0;

//my comand is a builtin? -> call it directly
//if not, call execvp: fork+execvp+wait

void	ft_exec(char **args)
{
	int				i;
	const char 		*curr;

	i = 0;
	curr = g_builtin[i].builtin_name;
	while(curr)
	{
		if (!strcmp(curr, args[0])) //trocar pelo da libft
		{
			status = g_builtin[i].foo(args);
			return;
		}
		++i;
	}
}

void ft_launch(char **args)
{
	if (ft_fork() == CELL_Jr)
		ft_execvp(args[0], args);
	else
		ft_wait(&status);

}