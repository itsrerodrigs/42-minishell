#include <stdio.h>
#include "../inc/minishell.h"

int main(void)
{
    t_shell shell;
    char *envp[] = {
        "HOME=/home/user",
        "OLDPWD=/tmp",
        NULL
    };
    char *args1[] = {"cd", NULL};
    char *args2[] = {"cd", "/tmp", NULL};
    char *args3[] = {"cd", "/invalid_path", NULL};

    shell.envp = envp;

    // Teste 1: Sem argumentos (deve ir para HOME)
    printf("Teste 1: cd sem argumentos\n");
    if (builtin_cd(&shell, args1) == 0)
        printf("Diretório alterado para HOME com sucesso.\n");
    else
        printf("Erro ao alterar para HOME.\n");

    // Teste 2: Com argumento válido
    printf("\nTeste 2: cd para /tmp\n");
    if (builtin_cd(&shell, args2) == 0)
        printf("Diretório alterado para /tmp com sucesso.\n");
    else
        printf("Erro ao alterar para /tmp.\n");

    // Teste 3: Com argumento inválido
    printf("\nTeste 3: cd para /invalid_path\n");
    if (builtin_cd(&shell, args3) != 0)
        printf("Erro esperado ao tentar alterar para /invalid_path.\n");
    else
        printf("Erro: Diretório inválido foi aceito.\n");

    return 0;
}