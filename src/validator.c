#include <gg_validator.h>

extern int validate_arguments(int args, char *argv[])
{
	int i;
	printf("args is %d\n", args);
	for (i = 0; i < args; ++i)
	{
		fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
	}
	return 1;
}
extern void print_usage(char *prog_name)
{
	fprintf(stdout, "usage:\n");
	fprintf(stdout, "%s <deck_size> <balls_number> <balls_coordinates> <holes_coordinates> <walls_coordinates>\n", prog_name);
}
