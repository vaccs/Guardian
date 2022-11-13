
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct expression_inheritance set_contains_expression_inheritance = {
	.print_source = set_contains_expression_print_source,
	.evaluate = set_contains_expression_evaluate,
	.print = set_contains_expression_print,
	.free = free_set_contains_expression,
};

