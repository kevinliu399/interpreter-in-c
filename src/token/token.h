#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{
	T_ILLEGAL,
	T_EOF,

	// identifiers, literals
	T_IDENT,
	T_INT,
	T_STRING,

	//operators
	T_ASSIGN,
	T_PLUS,
	T_MINUS,
	T_BANG,
	T_SLASH,
	T_ASTERISK,
	T_PERCENT,
	T_LT,
	T_GT,
	T_EQ,
	T_NOT_EQ,
	T_AND,
	T_OR,

	//delimiters
	T_COMMA,
	T_SEMICOLON,
	T_LPAREN,
	T_RPAREN,
	T_LBRACE,
	T_RBRACE,
	T_LBRACKET,
	T_RBRACKET,
	T_COLON,

	//keywords
	T_FUNCTION,
	T_LET,
	T_IF,
	T_ELSE,
	T_RETURN,
	T_TRUE,
	T_FALSE,
	T_WHILE
} TokenType;

typedef struct
{
    TokenType type;
    char *literal;
} Token;

Token *new_token(TokenType type, char *literal);
void free_token(Token *token);

#endif // TOKEN_H