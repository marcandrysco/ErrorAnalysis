#include "common.h"


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
	struct r_func_t *func;
	struct r_var_t *var;
	struct r_param_t *param = NULL;

	var = r_var_new(strdup("a"));

	r_param_append(&param, r_var_copy(var));

	func = r_func_new(
			r_expr_add(
				r_add_new(r_expr_var(r_var_copy(var)),
				r_expr_num(r_num_new(1)))
			),
		param);
	//func = r_func_new(r_expr_num(r_num_new(1)), param);
	//r_func_append(func, r_var_copy(var));
	
	printf("func: %C\n", r_func_chunk(func));

	r_func_delete(func);
	r_var_delete(var);

	if(hax_memcnt != 0)
		fprintf(stderr, "allocated memory: %d\n", hax_memcnt);

	return 0;
}
