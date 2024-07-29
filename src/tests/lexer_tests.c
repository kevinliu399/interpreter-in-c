#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../lexer/lexer.h"
#include "../token/token.h"

void test_next_token() {
    const char* input = "let five = 5;\n"
                        "let ten = 10;\n"
                        "\n"
                        "let add = fn(x, y) {\n"
                        "  x + y;\n"
                        "};\n"
                        "\n"
                        "let result = add(five, ten);\n"
                        "!-/*5;\n"
                        "5 < 10 > 5;\n"
                        "\n"
                        "if (5 < 10) {\n"
                        "    return true;\n"
                        "} else {\n"
                        "    return false;\n"
                        "}\n"
                        "\n"
                        "10 == 10;\n"
                        "10 != 9;\n";

    struct {
        TokenType expectedType;
        const char* expectedLiteral;
    } tests[] = {
        {T_LET, "let"},
        {T_IDENT, "five"},
        {T_ASSIGN, "="},
        {T_INT, "5"},
        {T_SEMICOLON, ";"},
        {T_LET, "let"},
        {T_IDENT, "ten"},
        {T_ASSIGN, "="},
        {T_INT, "10"},
        {T_SEMICOLON, ";"},
        {T_LET, "let"},
        {T_IDENT, "add"},
        {T_ASSIGN, "="},
        {T_FUNCTION, "fn"},
        {T_LPAREN, "("},
        {T_IDENT, "x"},
        {T_COMMA, ","},
        {T_IDENT, "y"},
        {T_RPAREN, ")"},
        {T_LBRACE, "{"},
        {T_IDENT, "x"},
        {T_PLUS, "+"},
        {T_IDENT, "y"},
        {T_SEMICOLON, ";"},
        {T_RBRACE, "}"},
        {T_SEMICOLON, ";"},
        {T_LET, "let"},
        {T_IDENT, "result"},
        {T_ASSIGN, "="},
        {T_IDENT, "add"},
        {T_LPAREN, "("},
        {T_IDENT, "five"},
        {T_COMMA, ","},
        {T_IDENT, "ten"},
        {T_RPAREN, ")"},
        {T_SEMICOLON, ";"},
        {T_BANG, "!"},
        {T_MINUS, "-"},
        {T_SLASH, "/"},
        {T_ASTERISK, "*"},
        {T_INT, "5"},
        {T_SEMICOLON, ";"},
        {T_INT, "5"},
        {T_LT, "<"},
        {T_INT, "10"},
        {T_GT, ">"},
        {T_INT, "5"},
        {T_SEMICOLON, ";"},
        {T_IF, "if"},
        {T_LPAREN, "("},
        {T_INT, "5"},
        {T_LT, "<"},
        {T_INT, "10"},
        {T_RPAREN, ")"},
        {T_LBRACE, "{"},
        {T_RETURN, "return"},
        {T_TRUE, "true"},
        {T_SEMICOLON, ";"},
        {T_RBRACE, "}"},
        {T_ELSE, "else"},
        {T_LBRACE, "{"},
        {T_RETURN, "return"},
        {T_FALSE, "false"},
        {T_SEMICOLON, ";"},
        {T_RBRACE, "}"},
        {T_INT, "10"},
        {T_EQ, "=="},
        {T_INT, "10"},
        {T_SEMICOLON, ";"},
        {T_INT, "10"},
        {T_NOT_EQ, "!="},
        {T_INT, "9"},
        {T_SEMICOLON, ";"},
        {T_EOF, ""}
    };

    Lexer* l = new_lexer(input);
    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < num_tests; i++) {
        Token* tok = next_token(l);
        
        if (tok->type != tests[i].expectedType) {
            fprintf(stderr, "Test[%d] - TokenType wrong. Expected=%s, got=%s\n",
                    i, token_type_name(tests[i].expectedType), token_type_name(tok->type));
            assert(0);
        }

        if (strcmp(tok->literal, tests[i].expectedLiteral) != 0) {
            fprintf(stderr, "Test[%d] - Literal wrong. Expected=%s, got=%s\n",
                    i, tests[i].expectedLiteral, tok->literal);
            assert(0);
        }

        free_token(tok);
    }

    lexer_free(l);
    printf("All tests passed!\n");
}

int main() {
    test_next_token();
    return 0;
}