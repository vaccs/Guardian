
#include "inheritance.h"

#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_index_expression_inheritance = {
	.evaluate = list_index_expression_evaluate,
	.print = list_index_expression_print,
	.free = free_list_index_expression,
};

