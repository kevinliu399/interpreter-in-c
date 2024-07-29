#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
    TokenType *tok = (TokenType *)malloc(sizeof(TokenType));
    if (tok == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for token\n");
        exit(1);
    }

    // skip all whitespace
    skip_whitespace(lexer);

    switch (lexer -> ch)
    {
        case '=':
            // for == 
            if (peek_char(lexer) == '=')
            {
                read_char(lexer);
                *tok = T_EQ;
            }
            else
            {
                *tok = T_ASSIGN;
            }
            break;
    }


    return tok;
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
static char* peek_char(Lexer *l)
{
    if (l->read_position >= strlen(l->input))
    {
        return '\0';
    } else {
        return l -> input[l -> read_position];
    }
}

static const char *read_identifier(Lexer *l);
static TokenType lookup_ident(char *ident);
static char* read_string(Lexer *l);
