
#include "inheritance.h"

#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance comparison_expression_inheritance = {
	.evaluate = comparison_expression_evaluate,
	.print = comparison_expression_print,
	.free = free_comparison_expression,
};

