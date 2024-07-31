#ifndef AST_H
#define AST_H

#define MAX_IDENT_LENGTH 32
// #define MAX_OPERATOR_LENGTH 3

#include "../token/token.h"

// enum {
//     LOWEST = 1,
//     EQUALS,         // ==
//     LESSGREATER,    // < or >
//     SUM,            // - and +
//     PRODUCT,        // * and /
//     PREFIX,         // - or !x
//     CALL            // fn()
// };

enum expression_type {
    EXPR_INFIX = 1,
    EXPR_PREFIX,
    EXPR_INT,
    EXPR_IDENT,
    EXPR_BOOL,
    EXPR_IF,
    EXPR_FUNCTION,
};

enum statement_type {
    STMT_LET = 1,
    STMT_RETURN,
    STMT_EXPR,
};

struct identifier {
    struct Token token; 
    char value[MAX_IDENT_LENGTH];
};

struct identifiers {
    struct identifier *values;
    unsigned int size;
    unsigned int cap;
};

struct statement {
    enum statement_type type;
    struct Token token;
    struct identifier name;
    struct expression *value;
};

struct expression {
    enum expression_type type;
    union {
        struct identifier ident;
    };
} expression;

struct program {
    struct statement *statements;
    unsigned int cap;
    unsigned int size;
};

int get_token_precedence(struct Token t);
void expression_to_str(char *str, struct expression *expr);
void free_expression(struct expression *expr);

#endif // AST_H
