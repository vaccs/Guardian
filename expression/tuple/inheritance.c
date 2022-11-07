
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance tuple_expression_inheritance = {
	.print_source = tuple_expression_print_source,
	.evaluate = tuple_expression_evaluate,
	.print = tuple_expression_print,
	.free = free_tuple_expression,
};

