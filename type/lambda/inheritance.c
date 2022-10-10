
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef.h"
#include "generate_free_func.h"
#include "compare.h"
#include "free.h"

struct type_inheritance lambda_type_inheritance = {
	.generate_typedef = lambda_type_generate_typedef,
	.generate_free_func = lambda_type_generate_free_func,
	.compare = compare_lambda_types,
	.free = free_lambda_type,
};

