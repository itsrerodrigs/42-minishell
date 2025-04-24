#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/minishell.h"

void assert_equal_ptr(void *expected, void *actual, const char *message) {
    if (expected != actual) 
    {
        fprintf(stderr, "[FAIL] %s: Expected %p, got %p\n", message, expected, actual);
    } else 
    {
        printf("[PASS] %s\n", message);
    }
}

void test_validate_input_length() {
    char *valid_input = strdup("short input");
    char *long_input = malloc(2000);
    memset(long_input, 'a', 2000);
    long_input[1999] = '\0';

    printf("Testing validate_input_length...\n");
    assert_equal_ptr(valid_input, validate_input_length(valid_input), "Valid input");
    assert_equal_ptr(NULL, validate_input_length(long_input), "Input exceeds limit");

    free(valid_input);
    free(long_input);
}

int main() 
{
    printf("Running tests...\n");
    test_validate_input_length();
    return 0;
}

// void test_get_tokens() {
//     char *input = strdup("echo \"Hello World\"");
//     char **tokens = get_tokens(input);

//     printf("Testing get_tokens...\n");
//     if (strcmp(tokens[0], "echo") == 0 && strcmp(tokens[1], "Hello World") == 0) {
//         printf("[PASS] Tokens are correct\n");
//     } else {
//         printf("[FAIL] Tokens are incorrect\n");
//     }

//     free_tokens(tokens);
//     free(input);
// }

// void test_ft_malloc() {
//     void *ptr = ft_malloc(10);

//     printf("Testing ft_malloc...\n");
//     if (ptr != NULL) {
//         printf("[PASS] Memory allocated successfully\n");
//     } else {
//         printf("[FAIL] Memory allocation failed\n");
//     }

//     free(ptr);
// }

// void test_ft_exec() {
//     char *args[] = {"cd", "/home", NULL};
//     g_builtin[0] = (t_builtin){"cd", ft_cd}; // Example built-in initialization

//     printf("Testing ft_exec...\n");
//     ft_exec(args); // Check if the correct built-in function is called
// }
