
#include "inheritance.h"

#include "evaluate.h"
#include "free.h"

struct expression_inheritance funccall_expression_inheritance = {
	.evaluate = funccall_expression_evaluate,
	.free = free_funccall_expression,
};

