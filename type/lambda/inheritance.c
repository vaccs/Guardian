
#include <debug.h>

#include "generate_typedef.h"
#include "generate_free_func.h"
#include "generate_print_func.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance lambda_type_inheritance = {
	.generate_typedef = lambda_type_generate_typedef,
	.generate_print_func = lambda_type_generate_print_func,
	.generate_free_func = lambda_type_generate_free_func,
	
	.compare = compare_lambda_types,
	.print = lambda_type_print,
	.free = free_lambda_type,
};

