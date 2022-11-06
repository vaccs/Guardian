
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance logical_or_expression_inheritance = {
	.print_source = logical_or_expression_print_source,
	.evaluate = logical_or_expression_evaluate,
	.print = logical_or_expression_print,
	.free = free_logical_or_expression,
};

