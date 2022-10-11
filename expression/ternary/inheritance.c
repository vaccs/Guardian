
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance ternary_expression_inheritance = {
	.evaluate = ternary_expression_evaluate,
	.print_source = ternary_expression_print_source,
	.print = ternary_expression_print,
	.free = free_ternary_expression,
};

