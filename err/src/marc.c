/* marc's test code */

#include "common.h"

void test_marc()
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
}
