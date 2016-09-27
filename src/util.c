#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <gg_util.h>


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
const char *get_string(const char *base, const char *func)
{
	static char buffer[1024];
	memset(buffer, 0, 1024);
	strcpy(buffer, base);
	strcpy(&buffer[strlen(base)], func);
	return buffer;
}
