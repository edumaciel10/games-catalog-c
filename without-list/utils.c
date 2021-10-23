#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void boolean_print(boolean bool)
{
    if(bool == TRUE)
    {
        printf("TRUE\n");
    }
    else if(bool == FALSE)
    {
        printf("FALSE\n");
    }
    else
    {
        printf("ERRO\n");
    }
}

void getString(char str[]) {
    setbuf(stdin, 0);
    if (!scanf("%[^(\r|\n)]%*c", str))
    {
        exit(1);
    }
}
