
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance all_form_expression_inheritance = {
	.evaluate = all_form_expression_evaluate,
	.print_source = all_form_expression_print_source,
	.print = all_form_expression_print,
	.free = free_all_form_expression,
};

