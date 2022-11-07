
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance tuple_index_expression_inheritance = {
	.print_source = tuple_index_expression_print_source,
	.evaluate = tuple_index_expression_evaluate,
	.print = tuple_index_expression_print,
	.free = free_tuple_index_expression,
};

