#include "token.h"
#include <stdio.h>

// Create a new token with the given type and literal
Token* new_token(TokenType type, char* literal) {
    Token* token = (Token*)malloc(sizeof(Token)); // Allocate memory for the token
    if (token == NULL) {
        fprintf(stderr, "Failed to allocate memory for token\n");
        exit(1);
    }
    token->type = type;
    token->literal = literal;
    if (literal == NULL) {
        free_token(token);
        return NULL;
    }

    return token;
}

// Free the memory allocated for the token
void free_token(Token* token) {
    if (token == NULL) {
        return;
    }

    if (token -> type != EOF) {
        free(token->literal);
    }

    free(token);
}

// we need to map the token type to a string representation
char* get_token_type(TokenType t) {
    switch(t) {
        case IDENT: return "IDENT";
        case INT: return "INT";
        case ILLEGAL: return "ILLEGAL";
        case EOF: return "EOF";
        case ASSIGN: return "ASSIGN";
        case PLUS: return "PLUS";
        case COMMA: return "COMMA";
        case SEMICOLON: return "SEMICOLON";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case FUNCTION: return "FUNCTION";
        case LET: return "LET";
        default: return "UNKNOWN";
    }
}