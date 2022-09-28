
#include "inheritance.h"

#include "evaluate.h"
#include "free.h"

struct expression_inheritance lambda_expression_inheritance = {
	.evaluate = lambda_expression_evaluate,
	.free = free_lambda_expression,
};

