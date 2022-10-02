
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance literal_expression_inheritance = {
	.print_source = literal_expression_print_source,
	.evaluate = literal_expression_evaluate,
	.print = literal_expression_print,
	.free = free_literal_expression,
};

