#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_cd(void)
{
	t_token *head = malloc(sizeof(t_token));
	t_token *cur = head;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("cd");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_WORD;
	cur->value = ft_strdup("/home/user");
	cur->next = malloc(sizeof(t_token));
	cur = cur->next;

	cur->type = TOKEN_EOF;
	cur->value = NULL;
	cur->next = NULL;

	return head;
}

void test_builtin_cd(void)
{
	t_token *tokens = create_tokens_cd();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "cd") != 0)
		printf("cd: FAIL\n");
	else
		printf("cd: PASS\n");

	free_commands(&cmds);
	free_tokens(tokens);
}
