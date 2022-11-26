
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance tuple_init_expression_inheritance = {
	.print_source = tuple_init_expression_print_source,
	.evaluate = tuple_init_expression_evaluate,
	.print = tuple_init_expression_print,
	.free = free_tuple_init_expression,
};

