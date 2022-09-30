
#include "inheritance.h"
#include "print.h"
#include "free.h"

struct value_inheritance lambda_value_inheritance = {
	.print = lambda_value_print,
	.free = free_lambda_value,
};

