#ifndef REAL_EXPR_H
#define REAL_EXPR_H

/**
 * Integer structure.
 *   @mpz: The multi-precision integer.
 */
struct r_num_t {
	mpz_t mpz;
};

/**
 * Real expression enumerator.
 *   @r_num_v: Integer number.
 *   @r_var_v: Variable.
 *   @r_add_v: Addition.
 *   @r_mul_v: Multiplication.
 */
enum r_expr_e {
	r_num_v,
	r_var_v,
	r_add_v,
	r_mul_v
};

/**
 * Real data union.
 *   @num: Integer number.
 *   @var: Variable.
 *   @add: The addition.
 *   @mul: The multiplication.
 */
union r_expr_u {
	struct r_num_t *num;
	struct r_var_t *var;
	struct r_add_t *add;
	struct r_mul_t *mul;
};

/**
 * Real expression structure.
 *   @type: The type.
 *   @data: The data.
 */
struct r_expr_t {
	enum r_expr_e type;
	union r_expr_u data;
};

/**
 * Link structure.
 *   @expr: The expression.
 *   @prev, next: The previous and next links.
 */
struct r_link_t {
	struct r_expr_t *expr;
	struct r_link_t *prev, *next;
};


/*
 * expression declarations
 */
struct r_expr_t *r_expr_new(enum r_expr_e type, union r_expr_u data);
struct r_expr_t *r_expr_copy(struct r_expr_t *expr);
void r_expr_delete(struct r_expr_t *expr);

struct r_expr_t *r_expr_num(struct r_num_t *num);
struct r_expr_t *r_expr_var(struct r_var_t *var);
struct r_expr_t *r_expr_add(struct r_add_t *add);
struct r_expr_t *r_expr_mul(struct r_mul_t *mul);

void r_expr_print(const struct r_expr_t *expr, struct io_file_t file);
struct io_chunk_t r_expr_chunk(const struct r_expr_t *expr);

/*
 * number declarations
 */
struct r_num_t *r_num_new(int val);
struct r_num_t *r_num_copy(struct r_num_t *num);
void r_num_delete(struct r_num_t *num);

void r_num_print(const struct r_num_t *num, struct io_file_t file);
struct io_chunk_t r_num_chunk(const struct r_num_t *num);

#endif
