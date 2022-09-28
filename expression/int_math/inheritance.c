
#include "inheritance.h"

#include "evaluate.h"
#include "free.h"

struct expression_inheritance int_math_expression_inheritance = {
	.evaluate = int_math_expression_evaluate,
	.free = free_int_math_expression,
};

