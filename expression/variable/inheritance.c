
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance variable_expression_inheritance = {
	.print_source = variable_expression_print_source,
	.evaluate = variable_expression_evaluate,
	.print = variable_expression_print,
	.free = free_variable_expression,
};

