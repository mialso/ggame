#ifndef GGAME_VALIDATOR_H
#define GGAME_VALIDATOR_H

/*
#define QUOTE(data) #data
#define TO_S(macro) QUOTE(macro)

#define MAX_FIELD 1024
#define MIN_FIELD 3
*/
extern int validate_arguments(int args, char *argv[]);

/*
//extern char* validator_errors[];
static char* validator_errors[] = {
	"no error detected",
	"no arguments provided",
	"negative arguments provided",
	"zero arguments provided",
	"wrong field size provided: minimum value is "TO_S(MIN_FIELD)" and maximum is "TO_S(MAX_FIELD)"",
	"no balls number provided",
	"balls number is not valid: too high for provided deck size or lower 1",
	"wrong arguments provided"
};
*/

#endif
