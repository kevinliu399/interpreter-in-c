#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include <stdlib.h>

typedef struct
{
    char *input;
    size_t position;      // current position in input (points to current char)
    size_t read_position; // current reading position in input (after current char)
    char ch;           // current char under examination
} Lexer;


Lexer* new_lexer(char *input);
TokenType* next_token(Lexer *lexer);
void lexer_free(Lexer *lexer);

#endif // LEXER_H