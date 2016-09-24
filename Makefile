CFLAGS=-g -std=c99 -Wall -Wextra -Wpedantic -Iinclude/
# uncomment it if coordnate system starts with 0
#GG_DEFINES=-DGG_ZERO_CHECK
CC=gcc

BIN_DIR=bin

target=$(BIN_DIR)/run_game
test_target=$(BIN_DIR)/run_tests

headers=$(wildcard include/*.h)
objects=main.o validator.o
tests=validator_test.o validator.o

all: $(objects)
	@$(CC) $(CFLAGS) $(objects) -o $(target)
	@rm *.o
	@echo "make all done: binaries are in bin/ directory"

main.o: src/main.c $(headers)
	@$(CC) $(CFLAGS) -c src/main.c
# modules
validator.o: src/validator.c $(headers)
	@$(CC) $(GG_DEFINES) $(CFLAGS) -c src/validator.c

# tests
validator_test.o: test/validator_test.c
	@$(CC) $(GG_DEFINES) $(CFLAGS) -c $^

test: $(tests)
	@$(CC) $(CFLAGS) $^ -o $(test_target)
	@rm *.o
	./$(test_target)
