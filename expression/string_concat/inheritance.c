
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance string_concat_expression_inheritance = {
	.print_source = string_concat_expression_print_source,
	.evaluate = string_concat_expression_evaluate,
	.print = string_concat_expression_print,
	.free = free_string_concat_expression,
};

