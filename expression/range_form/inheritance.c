
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance range_form_expression_inheritance = {

	.print_source = range_form_expression_print_source,
	
	.evaluate = range_form_expression_evaluate,
	.print = range_form_expression_print,
	.free = free_range_form_expression,
};

