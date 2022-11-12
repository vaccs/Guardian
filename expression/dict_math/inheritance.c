
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance dict_math_expression_inheritance = {
	.print_source = dict_math_expression_print_source,
	.evaluate = dict_math_expression_evaluate,
	.print = dict_math_expression_print,
	.free = free_dict_math_expression,
};

