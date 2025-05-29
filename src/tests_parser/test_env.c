#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_env(void)
{
	t_token *head = malloc(sizeof(t_token));
	head->type = TOKEN_WORD;
	head->value = ft_strdup("env");
	head->next = malloc(sizeof(t_token));
	head->next->type = TOKEN_EOF;
	head->next->value = NULL;
	head->next->next = NULL;
	return head;
}

void test_builtin_env(void)
{
	t_token *tokens = create_tokens_env();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "env") != 0)
		printf("env: FAIL\n");
	else
		printf("env: PASS\n");

	free_commands(&cmds);
	free_tokens(tokens);
}
