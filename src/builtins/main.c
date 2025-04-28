#include <stdio.h>

int exec_builtin(char **args); // Protótipos

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        exec_builtin(&argv[1]);
    }
        return (0);
}
