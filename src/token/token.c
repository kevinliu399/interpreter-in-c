#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Create a new token with the given type and literal
Token *new_token(TokenType type, char *literal)
{
    Token *token = (Token *)malloc(sizeof(Token));
    if (token == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for token\n");
        exit(1);
    }

    token->type = type;
    if (literal != NULL)
    {
        // strdup : string duplication to isolate the literal from the input
        token->literal = strdup(literal);
        if (token->literal == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for token literal\n");
            exit(1);
        }
    }
    else
    {
        token->literal = NULL;
    }

    return token;
}

// Free the memory allocated for the token
void free_token(Token *token)
{
    if (token != NULL)
    {
        if (token->type != (TokenType)EOF)
        {
            free(token->literal);
        }
        free(token);
    }
}

// we need to map the token type to a string representation
char *token_type_name(int type) {
  switch (type) {
    case T_ASSIGN:
      return "ASSIGN";
    case T_PLUS:
      return "PLUS";
    case T_MINUS:
      return "MINUS";
    case T_BANG:
      return "BANG";
    case T_ASTERISK:
      return "ASTERISK";
    case T_SLASH:
      return "SLASH";
    case T_LT:
      return "LT";
    case T_GT:
      return "GT";
    case T_EQ:
      return "EQ";
    case T_NOT_EQ:
      return "NOT_EQ";
    case T_LET:
      return "LET";
    case T_TRUE:
      return "TRUE";
    case T_FALSE:
      return "FALSE";
    case T_IF:
      return "IF";
    case T_ELSE:
      return "ELSE";
    case T_RETURN:
      return "RETURN";
    case T_COLON:
      return "COLON";
    case T_SEMICOLON:
      return "SEMICOLON";
    case T_IDENT:
      return "IDENTIFIER";
    case T_INT:
      return "INTEGER";
    case T_LPAREN:
      return "LEFT_PAREN";
    case T_RPAREN:
      return "RIGHT_PAREN";
    case T_LBRACE:
      return "LEFT_BRACE";
    case T_RBRACE:
      return "RIGHT_BRACE";
    case T_LBRACKET:
      return "LEFT_BRACKET";
    case T_RBRACKET:
      return "RIGHT_BRACKET";
    case T_ILLEGAL:
      return "ILLEGAL";
    case T_COMMA:
      return "COMMA";
    case T_FUNCTION:
      return "FUNCTION";
    case T_EOF:
      return "EOF";
    case T_STRING:
      return "STRING";
    case T_AND:
      return "AND";
    case T_OR:
      return "OR";
  }
  return "UNKNOWN_TOKEN";
}