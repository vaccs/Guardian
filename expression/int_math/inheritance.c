
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

#include "print_source.h"

struct expression_inheritance int_math_expression_inheritance = {
	.evaluate = int_math_expression_evaluate,
	.print = int_math_expression_print,
	.free = free_int_math_expression,
	
	.print_source = int_math_expression_print_source,
};

