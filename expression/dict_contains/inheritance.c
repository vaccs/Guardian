
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance dict_contains_expression_inheritance = {
	.evaluate = dict_contains_expression_evaluate,
	.print = dict_contains_expression_print,
	.free = free_dict_contains_expression,
};

