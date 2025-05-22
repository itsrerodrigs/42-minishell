#ifndef TEST_H
# define TEST_H

#include "minishell.h"
#include "parser.h"

void	free_commands(t_command **cmds);

// Declarações das funções de teste
void test_builtin_echo(void);
void test_builtin_cd(void);
void test_builtin_pwd(void);
void test_builtin_export(void);
void test_builtin_unset(void);
void test_builtin_env(void);
void test_builtin_exit(void);

#endif
