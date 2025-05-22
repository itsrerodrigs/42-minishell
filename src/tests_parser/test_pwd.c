#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_pwd(void)
{
	t_token *head = malloc(sizeof(t_token));

	head->type = TOKEN_VALUE;
	head->value = ft_strdup("pwd");
	head->next = malloc(sizeof(t_token));
	head = head->next;

	head->type = TOKEN_EOF;
	head->value = NULL;
	head->next = NULL;

	return head - 1; // volta pro início
}

void test_builtin_pwd(void)
{
	t_token *tokens = create_tokens_pwd();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "pwd") != 0)
		printf("pwd: FAIL\n");
	else
		printf("pwd: PASS\n");

	free_commands(&cmds);
	free_tokens(&tokens);
}
