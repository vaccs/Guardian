
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

#include "print_source.h"

struct expression_inheritance float_math_expression_inheritance = {
	.evaluate = float_math_expression_evaluate,
	.print = float_math_expression_print,
	.free = free_float_math_expression,
	
	.print_source = float_math_expression_print_source,
};

