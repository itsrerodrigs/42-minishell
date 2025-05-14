/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renrodri <renrodri@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:33:32 by renrodri          #+#    #+#             */
/*   Updated: 2025/05/13 20:33:32 by renrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "builtins.h"

// Função para simular execução de comandos
void execute_builtin(t_shell *shell, char *input) {
    char *args[10]; // Um array simples para armazenar os argumentos do comando
    char *token;
    int i = 0;

    // Quebra o input em tokens e armazena no array args
    token = strtok(input, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Termina a lista de argumentos

    // Verifica o comando e chama a função apropriada
    if (args[0] == NULL) {
        return;
    }
    
    if (strcmp(args[0], "cd") == 0)
        builtin_cd(shell, args);
    else if (strcmp(args[0], "echo") == 0)
        builtin_echo(shell, args);
    else if (strcmp(args[0], "pwd") == 0)
        builtin_pwd(shell, args);
    else if (strcmp(args[0], "env") == 0)
        builtin_env(shell, args);
    else if (strcmp(args[0], "exit") == 0)
        builtin_exit(shell, args);
    else if (strcmp(args[0], "unset") == 0)
        builtin_unset(shell, args);
    else
        printf("Command not found: %s\n", args[0]);
}

int main(int argc, char *argv[], char *envp[])
 {
    (void)argc;
    (void)argv;
    t_shell shell;
    shell.envp = envp;
    shell.exit_status = 0;

    char input[100];
    
    // Simula o loop de um shell
    while (1) {
        printf("minishell> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            break;

        // Remove a nova linha no final da entrada
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
            break;

        execute_builtin(&shell, input);
    }

    return 0;
}
