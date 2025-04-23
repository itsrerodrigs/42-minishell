#include "../inc/minishell.h"


pid_t   ft_wait(int *status)
{
    pid_t   result;

    if(!status)
    {
        fprintf(stderr, RED "Wait: status argument required\n" RST);
        return(-1);
    }
    result = wait(status);
    if (result == -1)
        perror(RED "Wait failed\n" RST);
    if (WIFEXITED(*status))
        *status = WEXITSTATUS(*status);
    return(result);
}

void    ft_execvp(const char *file, char *const argv[])
{
    if (!file || !argv)
    {
        fprintf(stderr, RED "Wxecvp: invalid arguments\n" RST);
        exit(EXIT_FAILURE);
    }
    if (execvp(file, argv) == -1)
    {
        perror(RED "CELL_Jr failed\n" RST);
        exit(EX_UNAVAILABLE);
    }
}

pid_t   ft_fork(void)
{
    pid_t   pid;

    pid = fork();
    if (pid < 0)
    {
        perror(RED "Fork failed\n" RST);
        exit(EX_OSERR);
    }
    return(pid);
}


void	*ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr =  realloc(ptr, size);
	if (!new_ptr && size != 0)
	{
		perror(RED "Realloc failed\n" RST);
		exit(EXIT_FAILURE);
	}
	return(new_ptr);
}


void printbanner(void)
{
    p(C "Initializing Minishell.. \n" RST);
}

