
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_contains_expression_inheritance = {
	.evaluate = list_contains_expression_evaluate,
	.print = list_contains_expression_print,
	.free = free_list_contains_expression,
};

