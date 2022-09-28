
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance literal_expression_inheritance = {
	.evaluate = literal_expression_evaluate,
	.print = literal_expression_print,
	.free = free_literal_expression,
};

