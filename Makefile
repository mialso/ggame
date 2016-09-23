CFLAGS = -g -std=c99 -Wall -Wextra -Wpedantic -Iinclude/
CC=gcc

BIN_DIR=bin

target=$(BIN_DIR)/run_game

objects=main.o validator.o
headers=$(wildcard include/*.h)

all: $(objects)
	$(CC) $(CFLAGS) $(objects) -o $(target)
	@rm *.o

main.o: src/main.c $(headers)
	$(CC) $(CFLAGS) -c $^
validator.o: src/validator.c $(headers)
	$(CC) $(CFLAGS) -c $^
