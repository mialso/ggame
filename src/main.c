#include <gg_validator.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define STR(x) #x
#define TO_STR(string) STR(string)
#define AT(func) __FILE__ ":" TO_STR(__LINE__) ":"  TO_STR(func)

#define WALLS_DATA 4
#define BALLS_DATA 2

struct Array {
	uint64_t size;
	uint64_t *data;
};

int parse_walls_data(int args, char *argv[], struct Array *walls);
int parse_bh_data(int args, char *argv[], struct Array *balls, struct Array *holes);
void print_error(const char *location, char *var_name, int64_t data);
void print_debug(const char *location, char *var_name, int64_t data);
void print_debug_arr(uint64_t size, uint64_t *arr, char *name);

int main(int args, char *argv[])
{
	#define F main
	uint64_t res;

	struct Array balls;
	struct Array holes;
	struct Array walls;

	struct Deck *deck = NULL;

	// validate arguments
	if (0 != (res = validate_arguments(args, argv)))
	{
		exit(EXIT_FAILURE);
	}
	print_debug(AT(F), "validator done, res", res);
	// parse walls data from argv
	if (0 != (res = parse_walls_data(args, argv, &walls)))
	{
		exit(EXIT_FAILURE);
	}
	print_debug(AT(F), "parse_walls_data done, res", res);
	print_debug_arr(walls.size, walls.data, "walls");
	
	// parse balls and holes data
	if (0 != (res = parse_bh_data(args, argv, &balls, &holes)))
	{
			exit(EXIT_FAILURE);
	}

	// create deck
	/*
	if (0 != (res = init_deck(deck, deck_data)))
	{
		exit(EXIT_FAILURE);
	}
	*/
	exit(EXIT_SUCCESS);
}
/*
 * purpose: to detect if any walls are present in provided data
 * +populate the array and return pointer to new array
 */
int parse_walls_data(int args, char *argv[], struct Array *walls)
{
	#define F parse_walls_data
	uint64_t balls = atoi(argv[2]);
	uint64_t balls_and_holes_args = (balls * BALLS_DATA * 2) + 1;
	print_debug(AT(F), "balls_and_holes_args", balls_and_holes_args);
	int64_t args_left = args - 3 - balls_and_holes_args;
	print_debug(AT(F), "args_left", args_left);
	int64_t walls_number = 0;
	int64_t counter = 0;
	// check if walls data is present
	if (0 > args_left) {
		print_error(AT(F), "args", args);
		return -1;
	} else if (0 == args_left) {
		return 0;
	}
	// check if walls data is correct
	if (0 != (args_left % WALLS_DATA)) {
		print_error(AT(F), "args_left % WALLS_DATA", args_left % WALLS_DATA);
		return -1;
	}
	walls_number = atoi(argv[3]);
	print_debug(AT(F), "walls_number", walls_number);
	if (walls_number != (args_left/WALLS_DATA)) {
		print_error(AT(F), "args_left", args_left);
   		return -1;
	}	
	
	walls->data = calloc(args_left-1, sizeof(uint64_t));
	if (!walls->data) {
		print_error(AT(F), "memory error from args_left =", args_left-1);
		return -1;
	}
	for (counter = 1; counter <= (walls_number*WALLS_DATA); ++counter)
	{
		*(walls->data+counter-1) = atoi(argv[args-counter]);
	}
	walls->size = walls_number * WALLS_DATA;
	return 0;
}
int parse_bh_data(int args, char *argv[], struct Array *balls, struct Array *holes)
{
	#define F parse_bh_data
	print_debug(AT(F), "not implemented yet", 0);
	return 1;
}
void print_debug(const char *location, char *var_name, int64_t data)
{
	fprintf(stdout, "[DEBUG]: %s(): %s = %ld\n",
		location,
		var_name,
		data
	);
}	
void print_error(const char *location, char *var_name, int64_t data)
{
	fprintf(stderr, "[ERROR]: %s(): %s = %ld\n",
		location,
		var_name,
		data
	);
}
void print_debug_arr(uint64_t size, uint64_t *arr, char *name)
{
	char num_string[4];
	uint64_t i;
	if (100 < size) {
		print_debug(name, "array is too large, size", size);
		return;
	}
	for (i = 0; i < size; ++i)
	{
		snprintf(num_string, 3, "%zu", i);
		print_debug(name, num_string, (int)(*(arr+i)));
	}
}
