#ifndef GG_UTIL_H
#define GG_UTIL_H

#define STR(x) #x
#define TO_STR(string) STR(string)

#define AT get_string(__FILE__ ":"TO_STR(__LINE__)":", __func__)

extern void print_error(const char *location, char *var_name, int64_t data);
extern void print_debug(const char *location, char *var_name, int64_t data);
extern void print_debug_arr(uint64_t size, uint64_t *arr, char *name);
extern const char *get_string(const char * base, const char *func);

#endif
