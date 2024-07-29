CC = gcc

CFLAGS = -Wall -Wextra -g

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
TOKEN_DIR = $(SRC_DIR)/token
TEST_DIR = $(SRC_DIR)/tests

LEXER_SRC = $(LEXER_DIR)/lexer.c
TOKEN_SRC = $(TOKEN_DIR)/token.c
TEST_SRC = $(TEST_DIR)/lexer_tests.c

LEXER_OBJ = $(LEXER_DIR)/lexer.o
TOKEN_OBJ = $(TOKEN_DIR)/token.o
TEST_OBJ = $(TEST_DIR)/lexer_tests.o

TEST_EXEC = run_tests

# Targets
.PHONY: all clean test

all: $(TEST_EXEC)

$(TEST_EXEC): $(LEXER_OBJ) $(TOKEN_OBJ) $(TEST_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(LEXER_OBJ) $(TOKEN_OBJ) $(TEST_OBJ) $(TEST_EXEC)
