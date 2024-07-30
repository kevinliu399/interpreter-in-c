#include <stdio.h>
#include "repl/repl.h"


int main()
{
    printf("Welcome to Monkey Lang!\n");
    printf("Feel free to type in commands\n");
    repl_start();
}