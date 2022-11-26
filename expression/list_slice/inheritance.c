
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_slice_expression_inheritance = {
	.print_source = list_slice_expression_print_source,
	.evaluate = list_slice_expression_evaluate,
	.print = list_slice_expression_print,
	.free = free_list_slice_expression,
};

