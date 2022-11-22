
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance isexecutableby_form_expression_inheritance = {

	.print_source = isexecutableby_form_expression_print_source,
	
	.evaluate = isexecutableby_form_expression_evaluate,
	.print = isexecutableby_form_expression_print,
	.free = free_isexecutableby_form_expression,
};

