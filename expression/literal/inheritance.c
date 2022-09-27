
#include "inheritance.h"

#include "free.h"

struct expression_inheritance literal_expression_inheritance = {
	.free = free_literal_expression,
};

