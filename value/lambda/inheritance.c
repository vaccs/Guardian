
#include "inheritance.h"

#include "free.h"

struct value_inheritance lambda_value_inheritance = {
	.free = free_lambda_value,
};

