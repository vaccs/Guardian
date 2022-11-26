
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance string_index_expression_inheritance = {
	.print_source = string_index_expression_print_source,
	.evaluate = string_index_expression_evaluate,
	.print = string_index_expression_print,
	.free = free_string_index_expression,
};

