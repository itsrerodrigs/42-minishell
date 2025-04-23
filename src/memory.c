#include "../inc/minishell.h"

void *ft_malloc(size_t size)
{
    void *ptr;
    
    if (size == 0)
        return(NULL);
    ptr = malloc(size);
    if (!ptr)
    {
        perror(RED "Malloc failed\n" RST);
        exit (EXIT_FAILURE);
    }
    return(ptr);
}


void    *ft_getcwd(char *buf, size_t size)
{
    if (NULL == getcwd(buf, size))
    {
		perror (RED "Getcwd FAILED" RST);
		buf[0] = '\0';
	}
    return(buf);
}
