
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance has_expression_inheritance = {
	.evaluate = has_expression_evaluate,
	.print_source = has_expression_print_source,
	.print = has_expression_print,
	.free = free_has_expression,
};

