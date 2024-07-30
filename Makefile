CC = gcc
CFLAGS = -Wall -Wextra -g -I$(SRC_DIR)

SRC_DIR = src
LEXER_DIR = $(SRC_DIR)/lexer
TOKEN_DIR = $(SRC_DIR)/token
REPL_DIR = $(SRC_DIR)/repl
TEST_DIR = $(SRC_DIR)/tests

SRC_FILES = $(wildcard $(SRC_DIR)/*/*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)

TEST_EXEC = run_tests
MAIN_EXEC = monkey_lang

# Targets
.PHONY: all clean test

all: $(TEST_EXEC) $(MAIN_EXEC)

$(TEST_EXEC): $(filter-out main.o, $(OBJ_FILES)) $(TEST_DIR)/test_runner.o
	$(CC) $(CFLAGS) -o $@ $^

$(MAIN_EXEC): $(filter-out $(TEST_DIR)/%, $(OBJ_FILES)) main.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(OBJ_FILES) $(TEST_EXEC) $(MAIN_EXEC) main.o $(TEST_DIR)/*.o