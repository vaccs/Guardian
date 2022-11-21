
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance sum_form_expression_inheritance = {
	.evaluate = sum_form_expression_evaluate,
	.print_source = sum_form_expression_print_source,
	.print = sum_form_expression_print,
	.free = free_sum_form_expression,
};

