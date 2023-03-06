#include <stdio.h>
#include "minishell.h"

void    debug_print_char_array(char **args)
{
    printf("Tokens:");
    while (args != NULL && *args != NULL)
    {
        printf("`%s`", *args);
        args += 1;
    }
    printf("\n");
}

void    debug_print_t_execute(t_execute *execute)
{
    printf("t_execute: ");
    printf("order_str: `%s` order_numb: `%d`\n", \
            execute->order_str, execute->order_numb);
}
