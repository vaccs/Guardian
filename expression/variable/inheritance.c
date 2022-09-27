
#include "inheritance.h"

#include "free.h"

struct expression_inheritance variable_expression_inheritance = {
	.free = free_variable_expression,
};

