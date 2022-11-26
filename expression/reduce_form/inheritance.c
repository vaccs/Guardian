
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance reduce_form_expression_inheritance = {
	.evaluate = reduce_form_expression_evaluate,
	.print_source = reduce_form_expression_print_source,
	.print = reduce_form_expression_print,
	.free = free_reduce_form_expression,
};

