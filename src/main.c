#include <gg_validator.h>
#include <stdlib.h>

int main(int args, char *argv[])
{
	int res;
	printf("main ok\n");

	if (0 != (res = validate_arguments(args, argv)))
	{
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
