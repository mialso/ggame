#include <stdlib.h>
#include <stdint.h>

#include <gg_validator.h>
#include <gg_deck.h>
#include <gg_util.h>

#define WALLS_DATA 4
#define BALLS_DATA 2

struct Array {
	uint64_t size;
	uint64_t *data;
};

int parse_walls_data(int args, char *argv[], struct Array *walls);
int parse_bh_data(int args, char *argv[], struct Array *balls, struct Array *holes, uint64_t walls);

int main(int args, char *argv[])
{
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
	print_debug(AT, "validator done, res", res);
	// parse walls data from argv
	if (0 != (res = parse_walls_data(args, argv, &walls)))
	{
		exit(EXIT_FAILURE);
	}
	print_debug(AT, "parse_walls_data done, res", res);
	print_debug_arr(walls.size, walls.data, "walls");
	
	// parse balls and holes data
	if (0 != (res = parse_bh_data(args, argv, &balls, &holes, walls.size)))
	{
			exit(EXIT_FAILURE);
	}
	print_debug(AT, "parse_bh_data done, res", res);
	print_debug_arr(balls.size, balls.data, "balls");
	print_debug_arr(holes.size, holes.data, "holes");


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
	uint64_t balls = atoi(argv[2]);
	uint64_t balls_and_holes_args = (balls * BALLS_DATA * 2) + 1;
	print_debug(AT, "balls_and_holes_args", balls_and_holes_args);
	int64_t args_left = args - 2 - balls_and_holes_args;
	print_debug(AT, "args_left", args_left);
	int64_t walls_number = 0;
	int64_t walls_coords = 0;
	int64_t counter = 0;
	// check if walls data is present
	if (0 > args_left) {
		print_error(AT, "args", args);
		return -1;
	} else if (0 == args_left) {
		walls->size = 0;
		walls->data = NULL;
		return 0;
	}
	--args_left;
	// check if walls data is correct
	if (0 != (args_left % WALLS_DATA)) {
		print_error(AT, "args_left % WALLS_DATA", args_left % WALLS_DATA);
		return -1;
	}
	walls_number = atoi(argv[3]);
	walls_coords = walls_number*WALLS_DATA;
	print_debug(AT, "walls_number", walls_number);
	if (walls_coords != args_left) {
		print_error(AT, "args_left", args_left);
   		return -1;
	}	
	
	walls->data = calloc(walls_coords, sizeof(uint64_t));
	if (!walls->data) {
		print_error(AT, "memory error from walls_coords =", walls_coords);
		return -1;
	}
	for (counter = 1; counter <= walls_coords; ++counter)
	{
		*(walls->data+walls_coords-counter) = atoi(argv[args-counter]);
	}
	walls->size = walls_number * WALLS_DATA;
	return 0;
}
/*
 * purpose: to parse balls and holes data
 */
int parse_bh_data(int args, char *argv[], struct Array *balls, struct Array *holes, uint64_t walls)
{
	uint64_t counter = 1;
	uint64_t balls_number = atoi(argv[2])*BALLS_DATA;
	print_debug(AT, "balls_number", balls_number);
	uint64_t coords_to_parse = balls_number*2;
	print_debug(AT, "coords_to_parse", coords_to_parse);
	uint64_t start = (walls) ? 3 : 2;
	balls->size = balls_number;
	holes->size = balls_number;
	balls->data = calloc(balls->size, sizeof(uint64_t));
	if (!balls->data) {
		print_error(AT, "memory error from balls->size =", balls->size);
		return 1;
	}
	holes->data = calloc(holes->size, sizeof(uint64_t));
	if (!holes->data) {
		print_error(AT, "memory error from holes->size =", holes->size);
		return 2;
	}
	while (counter <= coords_to_parse)
	{
		if (counter <= coords_to_parse/2)
		{
			//print_debug(AT, "ball inserted at ", counter);
			*(balls->data+counter-1) = atoi(argv[start+counter]);
		}
	   	else
		{
			*(holes->data+counter-(coords_to_parse/2)-1) = atoi(argv[start+counter]);
			//print_debug(AT, "hole inserted at ", counter);
		}
		++counter;
	}
	return 0;
}
