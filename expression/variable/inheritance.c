
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "free.h"

struct expression_inheritance variable_expression_inheritance = {
	.evaluate = variable_expression_evaluate,
	.free = free_variable_expression,
};

