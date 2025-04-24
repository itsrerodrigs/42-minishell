#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inc/minishell.h"

void assert_equal_ptr(void *expected, void *actual, const char *message) {
    if (expected != actual) {
        fprintf(stderr, "[FAIL] %s: Expected %p, got %p\n", message, expected, actual);
    } else {
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

int main() {
    printf("Running tests...\n");
    test_validate_input_length();
    return 0;
}
