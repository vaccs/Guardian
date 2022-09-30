
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance parenthesis_expression_inheritance = {
	.evaluate = parenthesis_expression_evaluate,
	.print = parenthesis_expression_print,
	.free = free_parenthesis_expression,
};

