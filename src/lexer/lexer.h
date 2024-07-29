#ifndef LEXER_H
#define LEXER_H

#include "../token/token.h"
#include <stdlib.h>

typedef struct
{
    char *input;
    size_t position;      // current position in input (points to current char)
    size_t read_position; // current reading position in input (after current char)
    char ch;              // current char under examination
} Lexer;

Lexer *new_lexer(const char *input);
Token *next_token(Lexer *lexer);
void lexer_free(Lexer *lexer);
const char *token_type_name(TokenType type);

#endif // LEXER_H