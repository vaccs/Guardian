
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_concat_expression_inheritance = {
	.print_source = list_concat_expression_print_source,
	.evaluate = list_concat_expression_evaluate,
	.print = list_concat_expression_print,
	.free = free_list_concat_expression,
};

