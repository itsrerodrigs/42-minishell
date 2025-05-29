#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_unset(void)
{
	t_token *head = malloc(sizeof(t_token));
	t_token *cur = head;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("unset");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("VAR");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_EOF;
	cur->value = NULL;
	cur->next = NULL;

	return head;
}

void test_builtin_unset(void)
{
	t_token *tokens = create_tokens_unset();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "unset") != 0)
		printf("unset: FAIL\n");
	else
		printf("unset: PASS\n");

	free_commands(&cmds);
	free_tokens(tokens);
}
