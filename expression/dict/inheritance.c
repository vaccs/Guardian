
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance dict_expression_inheritance = {
	.print_source = dict_expression_print_source,
	.evaluate = dict_expression_evaluate,
	.print = dict_expression_print,
	.free = free_dict_expression,
};

