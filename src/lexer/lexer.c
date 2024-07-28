#include "lexer.h"
#include <stdio.h>

// Create a new lexer with the given input
Lexer *new_lexer(char *input)
{
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for lexer\n");
        exit(1);
    }

    // strdup : returns a pointer to a null-terminated byte string
    lexer->input = strdup(input);

    if (lexer->input == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for lexer input\n");
        exit(1);
    }

    lexer->position = 0;
    lexer->read_position = 0;
    lexer->ch = input[0]; // set the first character of the input

    return lexer;
}

static void skip_whitespace(Lexer *l) {
    while (l -> ch == ' ' || l -> ch == '\t' || l -> ch == '\n' || l -> ch == '\r') {
        read_char();
    }
}


TokenType* next_token(Lexer *lexer) {
    TokenType *tok = (TokenType *)malloc(sizeof(TokenType));
    if (tok == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for token\n");
        exit(1);
    }


}