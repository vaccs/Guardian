
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance set_expression_inheritance = {
	.print_source = set_expression_print_source,
	.evaluate = set_expression_evaluate,
	.print = set_expression_print,
	.free = free_set_expression,
};

