#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_export(void)
{
	t_token *head = malloc(sizeof(t_token));
	t_token *cur = head;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("export");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("VAR=value");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_EOF;
	cur->value = NULL;
	cur->next = NULL;

	return head;
}

void test_builtin_export(void)
{
	t_token *tokens = create_tokens_export();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "export") != 0)
		printf("export: FAIL\n");
	else
		printf("export: PASS\n");

	free_commands(&cmds);
	free_tokens(tokens);
}
