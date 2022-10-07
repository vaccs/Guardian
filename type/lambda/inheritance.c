
#include "inheritance.h"
#include "print_source.h"
#include "compare.h"
#include "free.h"

struct type_inheritance lambda_type_inheritance = {
	.print_source = lambda_type_print_source,
	.compare = compare_lambda_types,
	.free = free_lambda_type,
};

