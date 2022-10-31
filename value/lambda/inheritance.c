
#include <debug.h>

#include "inheritance.h"

#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance lambda_value_inheritance = {
	.print_source = lambda_value_print_source,
	
	.print = lambda_value_print,
	.free = free_lambda_value,
};

