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
/*
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
}*/

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
/*
 * Cria tokens simples para testar o parser.
 * A ideia aqui é simular: ls -l | grep txt > output.txt
 */
t_token *create_test_tokens(void)
{
    t_token *head = malloc(sizeof(t_token));
    t_token *current = head;

    if (!head)
        return NULL;

    // ls
    current->type = TOKEN_VALUE;
    current->value = "ls";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // -l
    current->type = TOKEN_VALUE;
    current->value = "-l";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // pipe |
    current->type = TOKEN_PIPE;
    current->value = "|";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // grep
    current->type = TOKEN_VALUE;
    current->value = "grep";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // txt
    current->type = TOKEN_VALUE;
    current->value = "txt";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // redirect output >
    current->type = TOKEN_REDIR_OUT;
    current->value = ">";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // output.txt
    current->type = TOKEN_VALUE;
    current->value = "output.txt";
    current->next = malloc(sizeof(t_token));
    current = current->next;

    // EOF
    current->type = TOKEN_EOF;
    current->value = NULL;
    current->next = NULL;

    return head;
}

void free_tokens(t_token **tokens)
{
    t_token *tmp;
    while (*tokens)
    {
        tmp = (*tokens)->next;
        free((*tokens)->value);
        free(*tokens);
        *tokens = tmp;
    }
    *tokens = NULL;
}

void print_commands(t_command *cmd)
{
    int i;
    while (cmd)
    {
        printf("Command: %s\n", cmd->cmd ? cmd->cmd : "(null)");
        printf("Args:");
        if (cmd->args)
        {
            i = 0;
            while (cmd->args[i])
            {
                printf(" %s", cmd->args[i]);
                i++;
            }
        }
        printf("\n");
        if (cmd->redirs)
        {
            t_redirect *redir = cmd->redirs;
            while (redir)
            {
                printf("Redirect: type %d, file %s\n", redir->type, redir->filename);
                redir = redir->next;
            }
        }
        printf("Is pipe: %d\n\n", cmd->is_pipe);
        cmd = cmd->next;
    }
}

int main(void)
{
    t_token *tokens = create_test_tokens();
    if (!tokens)
    {
        printf("Failed to create tokens.\n");
        return (1);
    }

    t_command *cmds = parse_tokens(tokens);
    if (!cmds)
    {
        printf("Parsing failed.\n");
        free_tokens(&tokens);
        return (1);
    }

    print_commands(cmds);

    free_tokens(&tokens);
    // Aqui você deveria liberar a lista de comandos e redirecionamentos também
    // para evitar leaks, mas vamos deixar isso para uma próxima etapa.

    return (0);
}

