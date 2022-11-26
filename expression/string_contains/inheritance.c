
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance string_contains_expression_inheritance = {
	.print_source = string_contains_expression_print_source,
	.evaluate = string_contains_expression_evaluate,
	.print = string_contains_expression_print,
	.free = free_string_contains_expression,
};

