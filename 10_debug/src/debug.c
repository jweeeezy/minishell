#include <stdio.h>
#include "minishell.h"

void    debug_print_tokens(char **args)
{
    printf("Tokens:");
    while (args != NULL && *args != NULL)
    {
        printf("`%s`", *args);
        args += 1;
    }
    printf("\n");
}

