
#include "inheritance.h"
#include "evaluate.h"
#include "free.h"

struct expression_inheritance literal_expression_inheritance = {
	.evaluate = literal_expression_evaluate,
	.free = free_literal_expression,
};

