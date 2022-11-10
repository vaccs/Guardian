
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance logical_and_expression_inheritance = {
	.print_source = logical_and_expression_print_source,
	.evaluate = logical_and_expression_evaluate,
	.print = logical_and_expression_print,
	.free = free_logical_and_expression,
};

