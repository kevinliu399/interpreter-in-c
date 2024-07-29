#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../token/token.h"

#define MAX_IDENT_LENGTH 255

// Create a new lexer with the given input
Lexer *new_lexer(char *input)
{
    Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
    if (lexer == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for lexer\n");
        exit(1);
    }

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

TokenType *next_token(Lexer *lexer)
{
	TokenType *token;

    // skip all whitespace
    skip_whitespace(lexer);

    switch (lexer -> ch)
    {
        case '=':
            if (peek_char(lexer) == '=')
            {
                read_char(lexer);
                token = create_token(T_EQ, "==");
            }
            else
            {
                token = create_token(T_ASSIGN, "=");
            }
            break;
        case '+':
            token = create_token(T_PLUS, "+");
            break;
        case '-':
            token = create_token(T_MINUS, "-");
            break;
        case '!':
            if (peek_char(lexer) == '=')
            {
                read_char(lexer);
                token = create_token(T_NOT_EQ, "!=");
            }
            else
            {
                token = create_token(T_BANG, "!");
            }
            break;
        case '/':
            token = create_token(T_SLASH, "/");
            break;
        case '*':
            token = create_token(T_ASTERISK, "*");
            break;
        case '<':
            token = create_token(T_LT, "<");
            break;
        case '>':
            token = create_token(T_GT, ">");
            break;
        case ';':
            token = create_token(T_SEMICOLON, ";");
            break;
        case ',':
            token = create_token(T_COMMA, ",");
            break;
        case '(':
            token = create_token(T_LPAREN, "(");
            break;
        case ')':
            token = create_token(T_RPAREN, ")");
            break;
        case '{':
            token = create_token(T_LBRACE, "{");
            break;
        case '}':
            token = create_token(T_RBRACE, "}");
            break;
        case '[':
            token = create_token(T_LBRACKET, "[");
            break;
        case ']':
            token = create_token(T_RBRACKET, "]");
            break;
        case ':':
            token = create_token(T_COLON, ":");
            break;
        case '\0':
            token = create_token(T_EOF, "");
            break;
        case '"':
            token = create_token(T_STRING, read_string(lexer));
            break;
        default:
            if (is_letter(lexer -> ch))
            {
                // translate into a string
                char *ident = read_identifier(lexer);
                token = create_token(lookup_ident(ident), ident);
                free(ident);
                return token;
            }
            else if (is_digit(lexer -> ch))
            {
                char *num = read_number(lexer);
                token = create_token(T_INT, num);
                free(num);
                return token;
            }
            else
            {
                token = create_token(T_ILLEGAL, "");
            }

    }

    read_char(lexer);
    return token;
}

void lexer_free(Lexer *lexer)
{
    free(lexer->input);
    free(lexer);
}

/****************************************************
 *                PRIVATE FUNCTIONS                 *
 ****************************************************/

static void read_char(Lexer *l)
{
    if (l->read_position >= strlen(l->input))
    {
        l->ch = 0;
    }
    else
    {
        l->ch = l->input[l->read_position];
    }
    l->position = l->read_position;
    l->read_position += 1;
}

static void skip_whitespace(Lexer *l)
{
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r')
    {
        read_char(l);
    }
}

static bool is_letter(char ch)
{
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

static bool is_digit(char ch)
{
    return '0' <= ch && ch <= '9';
}

static char *read_number(Lexer *l) {
  char *num = malloc(MAX_IDENT_LENGTH);
  char *current = num;
  while (is_digit(l -> ch)) {
    *current = l -> ch;
    current += 1;
    read_char(l);
  }
  *current = '\0';
  return num;
}

// we need peek char to check the next character without consuming it
static char peek_char(Lexer *l)
{
    if (l->read_position >= strlen(l->input))
    {
        return '\0';
    } else {
        return l -> input[l -> read_position];
    }
}

static const char *read_identifier(Lexer *l)
{
    char *ident = malloc(MAX_IDENT_LENGTH);
    char *current = ident;
    while (is_letter(l -> ch))
    {
        *current = l -> ch;
        current += 1;
        read_char(l);
    }

    *current = '\0';
    return ident;
}

// mapping of keywords to their respective token types
static TokenType lookup_ident(char *ident)
{
    if (strcmp(ident, "let") == 0)
    {
        return T_LET;
    }
    else if (strcmp(ident, "fn") == 0)
    {
        return T_FUNCTION;
    }
    else if (strcmp(ident, "if") == 0)
    {
        return T_IF;
    }
    else if (strcmp(ident, "else") == 0)
    {
        return T_ELSE;
    }
    else if (strcmp(ident, "return") == 0)
    {
        return T_RETURN;
    }
    else if (strcmp(ident, "true") == 0)
    {
        return T_TRUE;
    }
    else if (strcmp(ident, "false") == 0)
    {
        return T_FALSE;
    }
    else if (strcmp(ident, "while") == 0)
    {
        return T_WHILE;
    }
    return T_IDENT;
}

static char* read_string(Lexer *l)
{
    char *str = malloc(MAX_IDENT_LENGTH);
    char *current = str;
    read_char(l); // skip the first "
    while (l -> ch != '"' && l -> ch != '\0')
    {
        *current = l -> ch;
        current += 1;
        read_char(l);
    }
    *current = '\0';
    return str;
}
