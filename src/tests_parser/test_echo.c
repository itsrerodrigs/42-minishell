#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_echo(void)
{
	t_token *head = malloc(sizeof(t_token));
	t_token *cur = head;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("echo");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("hello");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("world");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_EOF;
	cur->value = NULL;
	cur->next = NULL;

	return head;
}

void test_builtin_echo(void)
{
	t_token *tokens = create_tokens_echo();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "echo") != 0)
		printf("echo: FAIL\n");
	else
		printf("echo: PASS\n");

	free_commands(&cmds);
	free_tokens(tokens);
}
