#include <gg_validator.h>

int main(int args, char *argv[])
{
	int res;
	printf("main ok\n");

	if (0 != (res = validate_arguments(args, argv)))
	{
		fprintf(stderr, "wrong aruments provided, exiting...\n");
		print_usage(argv[0]);
	}
	
	return 0;
}
