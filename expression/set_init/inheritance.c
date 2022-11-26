
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance set_init_expression_inheritance = {
	.print_source = set_init_expression_print_source,
	.evaluate = set_init_expression_evaluate,
	.print = set_init_expression_print,
	.free = free_set_init_expression,
};

