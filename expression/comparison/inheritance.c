
#include <debug.h>

#include "inheritance.h"

#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance comparison_expression_inheritance = {
	.print_source = comparison_expression_print_source,
	.evaluate = comparison_expression_evaluate,
	.print = comparison_expression_print,
	.free = free_comparison_expression,
};

