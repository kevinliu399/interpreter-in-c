#include "repl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/lexer.h"
#include "../token/token.h"
#include <sys/types.h>

#define MAX_LINE_LEN 128
#define PROMPT ">> "

extern void repl_start(void)
{
    Token *tok;
    ssize_t num_chars = 0;
    size_t bufsize = MAX_LINE_LEN + 1;
    char *buffer = (char *)malloc(bufsize * sizeof(char));

    if (buffer == NULL)
    {
        fprintf(stderr, "Error: unable to allocate buffer for input\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        printf("%s", PROMPT);
        num_chars = getline(&buffer, &bufsize, stdin);
        if (num_chars > 1)
        {
            Lexer* l = new_lexer(buffer);
            for (tok = next_token(l); tok->type != T_EOF; tok = next_token(l))
            {
                printf("Type: %s, Literal: %s\n", token_type_name(tok->type), tok->literal);
                free_token(tok);
            }
            printf("\n");
            lexer_free(l);
        }
    } while (num_chars != EOF);

    free(buffer);
    printf("\n");
}