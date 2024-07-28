#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
    T_ILLEGAL,
    T_EOF,

    // Identifiers + literals
    T_IDENT,
    T_INT,

    // Operators
    T_ASSIGN,
    T_PLUS,

    // Delimiters
    T_COMMA,
    T_SEMICOLON,

    T_LPAREN,
    T_RPAREN,
    T_LBRACE,
    T_RBRACE,

    // Keywords
    T_FUNCTION,
    T_LET,
} TokenType;

typedef struct
{
    TokenType type;
    char *literal;
} Token;

Token *new_token(TokenType type, char *literal);
void free_token(Token *token);

#endif // TOKEN_H