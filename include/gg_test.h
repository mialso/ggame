#ifndef GG_TEST_H
#define GG_TEST_H

#define OUT_BUF_SIZE 4096
#define ERR_BUF_SIZE 4096
/*
 * test suite data structure declaration
 */
struct Test_suite {
	char *name;
	uint64_t cases_initialized;
	uint64_t cases_init_error;
	uint64_t cases_success;
	uint64_t cases_error;
};

/*
 * test case strucure declaration
 */
struct Test_case {
	char *name;
	uint64_t ready;
	int64_t success_result;
	int64_t test_result;
	int args;
	char **argv;
};

/*
 * interface to be used in test run ???
 * TODO am i able to move it to test main???
 */
extern void case_error(uint64_t case_num);
extern void case_success(uint64_t case_num);

/*
 * extern references to be initialized by test suites
 * each test suite must be mentioned here
 */
extern struct Test_suite validator_test;

#endif
