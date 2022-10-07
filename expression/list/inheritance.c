
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_expression_inheritance = {
	.print_source = list_expression_print_source,
	.evaluate = list_expression_evaluate,
	.print = list_expression_print,
	.free = free_list_expression,
};

