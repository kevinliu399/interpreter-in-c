# ifndef TOKEN_H
# define TOKEN_H

typedef enum {
    ILLEGAL,
    EOF,

    // Identifiers + literals
    IDENT, 
    INT,

    // Operators
    ASSIGN,
    PLUS,

    // Delimiters
    COMMA,
    SEMICOLON,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,

    // Keywords
    FUNCTION,
    LET,
} TokenType;

typedef struct {
    TokenType type;
    char* literal;
} Token;

Token* new_token(TokenType type, char* literal);
void free_token(Token* token);


#endif // TOKEN_H