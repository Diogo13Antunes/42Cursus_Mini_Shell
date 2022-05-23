#include "minishell.h"

int main (void)
{
    char *str;
    
    while (1)
    {
        str = readline("minishell >");
        printf("%s\n", str);
        free(str);
    }
    return (0);
}