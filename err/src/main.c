#include "common.h"


/*
 * test declarations
 */
void test_marc();


/**
 * Abstract domain information structure.
 *   @real, err: The real and error functions.
 */
struct mm_abs_t {
	struct r_func_t *real, *err;
};

struct mm_abs_t *mm_abs_new(struct r_func_t *func)
{
	struct mm_abs_t *abs;

	abs = malloc(sizeof(struct mm_abs_t));
	abs->real = func;
	//abs->err = r_func_new();

	return abs;
}

void mm_abs_delete(struct mm_abs_t *abs)
{
	r_func_delete(abs->real);
	free(abs);
}


/**
 * Main entry function.
 *   @argc: The number of arguments.
 *   @argv: The argument array.
 *   &returns: The exit status.
 */
int main(int argc, char **argv)
{
	test_marc();

	if(hax_memcnt != 0)
		fprintf(stderr, "allocated memory: %d\n", hax_memcnt);

	return 0;
}
