#include "../common.h"


/*
 * local declarations
 */
static void expr_proc(struct io_file_t file, void *arg);
static void num_proc(struct io_file_t file, void *arg);


/**
 * Create a expression.
 *   @type: The type.
 *   @data: Consumed. The data.
 *   &returns: The expression.
 */
struct r_expr_t *r_expr_new(enum r_expr_e type, union r_expr_u data)
{
	struct r_expr_t *expr;

	expr = malloc(sizeof(struct r_expr_t));
	*expr = (struct r_expr_t){ type, data };

	return expr;
}

/**
 * Copy an expression.
 *   @expr: The original expression.
 *   &returns: The copied expression.
 */
struct r_expr_t *r_expr_copy(struct r_expr_t *expr)
{
	switch(expr->type) {
	case r_num_v: return r_expr_num(r_num_copy(expr->data.num));
	case r_var_v: return r_expr_var(r_var_copy(expr->data.var));
	case r_add_v: return r_expr_add(r_add_copy(expr->data.add));
	case r_mul_v: return r_expr_mul(r_mul_copy(expr->data.mul));
	}

	fatal("Invalid real expression type.");
}

/**
 * Delete an expression.
 *   @expr: The expression.
 */
void r_expr_delete(struct r_expr_t *expr)
{
	switch(expr->type) {
	case r_num_v: r_num_delete(expr->data.num); break;
	case r_var_v: r_var_delete(expr->data.var); break;
	case r_add_v: r_add_delete(expr->data.add); break;
	case r_mul_v: r_mul_delete(expr->data.mul); break;
	}

	free(expr);
}


/**
 * Create a number expression.
 *   @num: The number.
 *   &returns: The expression.
 */
struct r_expr_t *r_expr_num(struct r_num_t *num)
{
	return r_expr_new(r_num_v, (union r_expr_u){ .num = num });
}

/**
 * Create a variable expression.
 *   @var: The variable.
 *   &returns: The expression.
 */
struct r_expr_t *r_expr_var(struct r_var_t *var)
{
	return r_expr_new(r_var_v, (union r_expr_u){ .var = var });
}

/**
 * Create an addition expression.
 *   @add: The addition.
 *   &returns: The expression.
 */
struct r_expr_t *r_expr_add(struct r_add_t *add)
{
	return r_expr_new(r_add_v, (union r_expr_u){ .add = add });
}

/**
 * Create a multiplication expression.
 *   @mul: The multiplication.
 *   &returns: The expression.
 */
struct r_expr_t *r_expr_mul(struct r_mul_t *mul)
{
	return r_expr_new(r_mul_v, (union r_expr_u){ .mul = mul });
}


/**
 * Print an expression.
 *   @expr: The expression.
 *   @file: The file.
 */
void r_expr_print(const struct r_expr_t *expr, struct io_file_t file)
{
	switch(expr->type) {
	case r_num_v: r_num_print(expr->data.num, file); break;
	case r_var_v: hprintf(file, "%s", expr->data.var->id); break;
	case r_add_v: r_add_print(expr->data.add, file); break;
	case r_mul_v: break;
	}
}

/**
 * Retrieve a chunk for a expression.
 *   @expr: The expression.
 *   &returns: The chunk.
 */
struct io_chunk_t r_expr_chunk(const struct r_expr_t *expr)
{
	return (struct io_chunk_t){ expr_proc, (void *)expr };
}
static void expr_proc(struct io_file_t file, void *arg)
{
	r_expr_print(arg, file);
}


/**
 * Create a new number.
 *   @val: The initial value.
 *   &returns: The number.
 */
struct r_num_t *r_num_new(int val)
{
	struct r_num_t *num;

	num = malloc(sizeof(struct r_num_t));
	mpz_init_set_si(num->mpz, val);

	return num;
}

/**
 * Copy a number.
 *   @num: The original number.
 *   &returns: The copied number.
 */
struct r_num_t *r_num_copy(struct r_num_t *num)
{
	struct r_num_t *copy;

	copy = malloc(sizeof(struct r_num_t));
	mpz_init_set(copy->mpz, num->mpz);

	return copy;
}

/**
 * Delete a number.
 *   @num: The number.
 */
void r_num_delete(struct r_num_t *num)
{
	mpz_clear(num->mpz);
	free(num);
}


/**
 * Print a number.
 *   @num: The number.
 *   @file: The file.
 */
void r_num_print(const struct r_num_t *num, struct io_file_t file)
{
	unsigned int len = gmp_snprintf(NULL, 0, "%Zd", num->mpz);
	char buf[len + 1];

	gmp_sprintf(buf, "%Zd", num->mpz);
	io_file_write(file, buf, len);
}

/**
 * Retrieve a chunk for a number.
 *   @num: The number.
 *   &returns: The chunk.
 */
struct io_chunk_t r_num_chunk(const struct r_num_t *num)
{
	return (struct io_chunk_t){ num_proc, (void *)num };
}
static void num_proc(struct io_file_t file, void *arg)
{
	r_num_print(arg, file);
}
