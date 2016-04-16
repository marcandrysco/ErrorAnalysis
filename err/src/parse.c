#include "common.h"


/**
 * Parse structure.
 *   @path: The path.
 *   @file: The file.
 *   @ch: The current character.
 *   @line, col: The line and column.
 */
struct parse_t {
	char *path;
	struct io_file_t file;

	int ch;
	unsigned int line, col;
};


/*
 * local declarations
 */
static struct parse_t *parse_new(char *path, struct io_file_t file);


struct r_func_t *parse_func(const char *str)
{
	struct r_func_t *func;

	func = r_func_new(r_expr_num(r_num_new(1)), NULL);

	return func;
}


/**
 * Create a new parser.
 *   @path: The path.
 *   @file: The file.
 *   &returns: The parser.
 */
static struct parse_t *parse_new(char *path, struct io_file_t file)
{
	struct parse_t *parse;

	parse = malloc(sizeof(struct parse_t));
	parse->path = path;
	parse->file = file;
	parse->line = parse->col = 1;

	return parse;
}

/**
 * Delete a parser.
 *   @parse: The parser.
 */
void parse_delete(struct parse_t *parse)
{
	free(parse->path);
	free(parse);
}


/**
 * Create a string parser.
 *   @str: The string.
 *   &returns: The parser.
 */
struct parse_t *parse_str(const char *str)
{
	return parse_new(strdup("-"), io_file_str(str));
}


/**
 * Read the next character from the parser.
 *   @parse: The parser.
 */
int parse_next(struct parse_t *parse)
{
	if(io_file_read(parse->file, &parse->ch, 1) == 0)
		parse->ch = EOF;

	return parse->ch;
}
