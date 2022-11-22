
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance isaccessibleto_form_expression_inheritance = {

	.print_source = isaccessibleto_form_expression_print_source,
	
	.evaluate = isaccessibleto_form_expression_evaluate,
	.print = isaccessibleto_form_expression_print,
	.free = free_isaccessibleto_form_expression,
};

