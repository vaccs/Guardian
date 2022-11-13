
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

#include "print_source.h"

struct expression_inheritance tuple_concat_expression_inheritance = {
	.print_source = tuple_concat_expression_print_source,
	.evaluate = tuple_concat_expression_evaluate,
	.print = tuple_concat_expression_print,
	.free = free_tuple_concat_expression,
	
};

