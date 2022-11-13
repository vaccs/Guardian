
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance set_math_expression_inheritance = {
	.print_source = set_math_expression_print_source,
	.evaluate = set_math_expression_evaluate,
	.print = set_math_expression_print,
	.free = free_set_math_expression,
};

