#include <gg_validator.h>

/*
 * static procedure declarations
 */
static void print_usage(char *prog_name);

/*
 * purpose: to validate arugments, provided by user
 */
extern int validate_arguments(int args, char *argv[])
{
	if (0 == (args-1)) {
		goto error;
	}
	return 0;
	
error:
	fprintf(stderr, "wrong aruments provided, exiting...\n");
	print_usage(argv[0]);

	return 1;
}
void print_usage(char *prog_name)
{
	fprintf(stdout, "usage:\n");
	fprintf(stdout, "%s <deck_size> <balls_number> <balls_coordinates> <holes_coordinates> <walls_coordinates>\n", prog_name);
}
