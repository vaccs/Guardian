
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance int_math_expression_inheritance = {
	.evaluate = int_math_expression_evaluate,
	.print = int_math_expression_print,
	.free = free_int_math_expression,
};

