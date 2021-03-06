CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic -Iinclude/
#  uncomment it if coordnate system starts with 0
#GG_DEFINES=-DGG_ZERO_CHECK
CC := gcc

BIN_DIR := $(shell pwd)/bin/

target := $(BIN_DIR)run_game
test_target := $(BIN_DIR)run_tests

headers := $(wildcard include/*.h)
objects := main.o validator.o util.o
tests := validator_test.o validator.o

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o $(target)
	@rm *.o
	@echo "make 'all': done: binaries are at $(BIN_DIR)"
	@echo "to execute tests, run: 'make test'"

main.o: src/main.c $(headers)
	$(CC) $(CFLAGS) -c src/main.c
#  modules
validator.o: src/validator.c include/gg_validator.h
	$(CC) $(GG_DEFINES) $(CFLAGS) -c src/validator.c

util.o: src/util.c include/gg_util.h
	$(CC) $(GG_DEFINES) $(CFLAGS) -c src/util.c

#  tests
validator_test.o: test/validator_test.c
	$(CC) $(GG_DEFINES) $(CFLAGS) -c $^

test: $(tests)
	$(CC) $(CFLAGS) $^ -o $(test_target)
	@rm *.o
	bash -c "$(test_target)"
