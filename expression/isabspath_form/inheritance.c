
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance isabspath_form_expression_inheritance = {

	.print_source = isabspath_form_expression_print_source,
	
	.evaluate = isabspath_form_expression_evaluate,
	.print = isabspath_form_expression_print,
	.free = free_isabspath_form_expression,
};

