#include "token.h"
#include <stdio.h>

// Create a new token with the given type and literal
Token *new_token(TokenType type, char *literal)
{
    Token *token = (Token *)malloc(sizeof(Token)); // Allocate memory for the token
    if (token == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for token\n");
        exit(1);
    }
    token->type = type;
    token->literal = literal;
    if (literal == NULL)
    {
        free_token(token);
        return NULL;
    }

    return token;
}

// Free the memory allocated for the token
void free_token(Token *token)
{
    if (token == NULL)
    {
        return;
    }

    if (token->type != EOF)
    {
        free(token->literal);
    }

    free(token);
}

// we need to map the token type to a string representation
char *get_token_type(TokenType t)
{
    switch (t)
    {
    case T_IDENT:
        return "IDENT";
    case T_INT:
        return "INT";
    case T_ILLEGAL:
        return "ILLEGAL";
    case T_EOF:
        return "EOF";
    case T_ASSIGN:
        return "ASSIGN";
    case T_PLUS:
        return "PLUS";
    case T_COMMA:
        return "COMMA";
    case T_SEMICOLON:
        return "SEMICOLON";
    case T_LPAREN:
        return "LPAREN";
    case T_RPAREN:
        return "RPAREN";
    case T_LBRACE:
        return "LBRACE";
    case T_RBRACE:
        return "RBRACE";
    case T_FUNCTION:
        return "FUNCTION";
    case T_LET:
        return "LET";
    default:
        return "UNKNOWN";
    }
}