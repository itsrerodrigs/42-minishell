#include "minishell.h"
#include "parser.h"
#include "test.h"

t_token *create_tokens_exit(void)
{
	t_token *head = malloc(sizeof(t_token));
	head->type = TOKEN_VALUE;
	head->value = ft_strdup("exit");
	head->next = malloc(sizeof(t_token));
	head->next->type = TOKEN_EOF;
	head->next->value = NULL;
	head->next->next = NULL;
	return head;
}

void test_builtin_exit(void)
{
	t_token *tokens = create_tokens_exit();
	t_command *cmds = parse_tokens(tokens);

	if (!cmds || strcmp(cmds->cmd, "exit") != 0)
		printf("exit: FAIL\n");
	else
		printf("exit: PASS\n");

	free_commands(&cmds);
	free_tokens(&tokens);
}
