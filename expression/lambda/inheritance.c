
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance lambda_expression_inheritance = {
	.evaluate = lambda_expression_evaluate,
	.print = lambda_expression_print,
	.free = free_lambda_expression,
};

