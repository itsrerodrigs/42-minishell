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
#include <string.h>
#include "minishell.h"
#include "parser.h"

void free_tokens_partial(t_token *head)
{
    t_token *tmp;

    while (head)
    {
        tmp = head->next;
        if (head->value)
            free(head->value);
        free(head);
        head = tmp;
    }
}

t_token *create_test_tokens(void)
{
    t_token *head = malloc(sizeof(t_token));
    t_token *current = head;

    if (!head)
        return NULL;

    current->type = TOKEN_VALUE;
    current->value = ft_strdup("ls");
    if (!current->value)
    {
        free(current);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_VALUE;
    current->value = ft_strdup("-l");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_PIPE;
    current->value = ft_strdup("|");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_VALUE;
    current->value = ft_strdup("grep");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_VALUE;
    current->value = ft_strdup("txt");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_REDIR_OUT;
    current->value = ft_strdup(">");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_VALUE;
    current->value = ft_strdup("output.txt");
    if (!current->value)
    {
        free_tokens_partial(head);
        return NULL;
    }

    current->next = malloc(sizeof(t_token));
    if (!current->next)
    {
        free_tokens_partial(head);
        return NULL;
    }
    current = current->next;

    current->type = TOKEN_EOF;
    current->value = NULL;
    current->next = NULL;

    return head;
}

/* Função para liberar tokens */
void free_tokens(t_token **tokens)
{
    t_token *current;
    t_token *next;

    if (!tokens || !*tokens)
        return;
    current = *tokens;
    while (current)
    {
        next = current->next;

        // Libera a string duplicada no token
        if (current->value)
            free(current->value);

        // Libera o próprio token
        free(current);

        current = next;
    }
    *tokens = NULL;
}

/* Função para imprimir a lista de comandos */
void print_commands(t_command *cmd)
{
    int i;
    t_redirect *redir;

    while (cmd)
    {
        printf("Command: %s\n", cmd->cmd ? cmd->cmd : "(null)");

        if (cmd->args)
        {
            printf("Arguments:");
            for (i = 0; cmd->args[i]; i++)
                printf(" %s", cmd->args[i]);
            printf("\n");
        }
        else
        {
            printf("Arguments: (none)\n");
        }

        redir = cmd->redirs;
        while (redir)
        {
            printf("Redirection: ");
            if (redir->type == TOKEN_REDIR_OUT)
                printf("Output > ");
            else if (redir->type == TOKEN_REDIR_IN)
                printf("Input < ");
            else if (redir->type == TOKEN_APPEND)
                printf("Append >> ");
            else if (redir->type == TOKEN_HEREDOC)
                printf("Heredoc << ");
            else
                printf("Unknown ");

            printf("%s\n", redir->filename);
            redir = redir->next;
        }

        if (cmd->is_pipe)
            printf("Pipe to next command\n");

        printf("----\n");
        cmd = cmd->next;
    }
}

/* Função para liberar comandos e tudo que eles possuem */
void free_commands(t_command **cmd_list)
{
    t_command *current;
    t_command *next;

    if (!cmd_list || !*cmd_list)
        return;

    current = *cmd_list;
    while (current)
    {
        next = current->next;

        // NÃO libera current->cmd (aponta para token->value)
        // NÃO libera os args[i] (apontam para token->value)
        if (current->args)
            free(current->args);

        // Libera a lista de redirections, mas NÃO os filenames (apontam para token->value)
        while (current->redirs)
        {
            t_redirect *tmp = current->redirs;
            current->redirs = tmp->next;
            free(tmp);
        }

        free(current);
        current = next;
    }
    *cmd_list = NULL;
}

int main(void)
{
    t_token *tokens = create_test_tokens();
    t_command *cmd_list = parse_tokens(tokens);

    if (!cmd_list)
    {
        printf("Parsing failed\n");
        free_tokens(&tokens);
        return 1;
    }

    print_commands(cmd_list);

    free_commands(&cmd_list);
    free_tokens(&tokens);

    return 0;
}