
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance variable_expression_inheritance = {
	.evaluate = variable_expression_evaluate,
	.print = variable_expression_print,
	.free = free_variable_expression,
};

