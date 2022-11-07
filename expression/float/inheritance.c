
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance float_expression_inheritance = {
	.evaluate = float_expression_evaluate,
	.print_source = float_expression_print_source,
	.print = float_expression_print,
	.free = free_float_expression,
};

