
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance int_form_expression_inheritance = {
	.evaluate = int_form_expression_evaluate,
	.print_source = int_form_expression_print_source,
	.print = int_form_expression_print,
	.free = free_int_form_expression,
};

