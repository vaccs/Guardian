
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance crossmap_form_expression_inheritance = {
	.evaluate = crossmap_form_expression_evaluate,
	.print_source = crossmap_form_expression_print_source,
	.print = crossmap_form_expression_print,
	.free = free_crossmap_form_expression,
};

