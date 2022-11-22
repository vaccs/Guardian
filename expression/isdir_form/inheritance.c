
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance isdir_form_expression_inheritance = {

	.print_source = isdir_form_expression_print_source,
	
	.evaluate = isdir_form_expression_evaluate,
	.print = isdir_form_expression_print,
	.free = free_isdir_form_expression,
};

