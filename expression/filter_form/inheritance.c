
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance filter_form_expression_inheritance = {
	.evaluate = filter_form_expression_evaluate,
	.print_source = filter_form_expression_print_source,
	.print = filter_form_expression_print,
	.free = free_filter_form_expression,
};

