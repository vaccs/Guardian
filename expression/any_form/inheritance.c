
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance any_form_expression_inheritance = {
	.evaluate = any_form_expression_evaluate,
	.print_source = any_form_expression_print_source,
	.print = any_form_expression_print,
	.free = free_any_form_expression,
};

