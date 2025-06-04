// Adicione esta função em um novo arquivo (ex: src/builtins/printenv.c)
// E adicione a declaração dela em inc/minishell.h ou inc/builtins.h
// Não esqueça de adicioná-la ao seu array de builtins para que possa ser executada.

#include "minishell.h" // Inclua seu cabeçalho principal
#include <stdio.h>    // Para STDERR_FILENO, se não estiver em minishell.h

int builtin_printenv(t_shell *shell, char **args)
{
    int i;
    (void)args; // Não usamos argumentos para printenv simples

    if (!shell || !shell->envp)
    {
        ft_putendl_fd("printenv: environment not found", STDERR_FILENO);
        return (1);
    }
    i = 0;
    while (shell->envp[i])
    {
        ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
        i++;
    }
    return (0);
}
