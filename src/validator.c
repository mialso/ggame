#include <gg_validator.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <gg_util.h>

/*
#define QUOTE(data) #data
#define TO_S(macro) QUOTE(macro)
*/

#define MAX_FIELD 1024
#define MIN_FIELD 3

static char* validator_errors[] = {
	"no error detected",
	"no arguments provided",
	"negative arguments provided",
	"zero arguments provided",
	"wrong field size provided: minimum value is "TO_STR(MIN_FIELD)" and maximum is "TO_STR(MAX_FIELD)"",
	"wrong coordinates provided (greater than deck size)",
	"no balls number provided",
	"balls number is not valid: too high for provided deck size or lower 1",
	"wrong arguments provided"
};

enum validator_err_named {
	NO_ERROR,
	EMPTY_ARGUMENTS,
	NEGATIVE_ARGS,
	ZERO_ARGS,
	WRONG_FIELD_SIZE,
	WRONG_COORDS,
	NO_BALLS_NUMBER,
	BALLS_NUMBER_IS_NOT_VALID,
	WRONG_ARGUMENTS
} error;
/*
 * static procedure declarations
 */
static void print_usage(char *prog_name);
static int check_zero_negative(int size, char *arr[]);

/*
 * purpose: to validate arugments, provided by user
 */
extern int validate_arguments(int args, char *argv[])
{
	//uint64_t error = 0;
	int deck = 0;
	int balls = 0;
	uint64_t coords_start_num = 0;
	uint64_t counter = 0;
	// check empty arguments
	if (0 == (args-1)) {
		error = EMPTY_ARGUMENTS;
		goto error_exit;
	}
	// check negative arguments and optionally zero
	if (NEGATIVE_ARGS == (error = check_zero_negative(args, argv))
	#ifdef GG_ZERO_CHECK
			|| ZERO_ARGS == error
	#endif
		) {
		goto error_exit;
	}
	// check deck size to be valid
	deck = atoi(argv[1]);
	if ((MIN_FIELD > deck) || (MAX_FIELD < deck)) {
		error = WRONG_FIELD_SIZE;
		goto error_exit;
	}
	// check coordinates to be not larger than deck size
	coords_start_num = (args % 2) ? 2 : 3;
	counter = args-1;
	while(counter > coords_start_num)
	{
		if (deck < atoi(argv[counter])) {
			error = WRONG_COORDS;
			goto error_exit;
		}
		--counter;
	}

	if (2 > (args-1)) {
		error = NO_BALLS_NUMBER;
		goto error_exit;
	}
	balls = atoi(argv[2]);
	// check ball size to be valid
	if ((1 > balls) || (balls > (deck*deck/2))) {
		error = BALLS_NUMBER_IS_NOT_VALID;
		goto error_exit;
	}
	return 0;
	
error_exit:
	fprintf(stderr, "[validator.c]: <validate_arguments>: %s\n",
		validator_errors[error]
	);
	print_usage(argv[0]);

	return error;
}
int check_zero_negative(int size, char *arr[])
{
	int i;
	for (i = 1; i < size; ++i)
	{
		if (0 > atoi(arr[i])) {
			return 2;
		}
		if (0 == atoi(arr[i])) {
			return 3;
		}
	}
	return 0;
}
void print_usage(char *prog_name)
{
	fprintf(stdout, "usage:\n");
	fprintf(stdout, "%s <deck_size> <balls_number> <walls> <balls_coordinates> <holes_coordinates> <walls_coordinates>\n", prog_name);
}
