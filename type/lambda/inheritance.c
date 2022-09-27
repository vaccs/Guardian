
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct type_inheritance lambda_type_inheritance = {
	.compare = compare_lambda_types,
	.free = free_lambda_type,
};

