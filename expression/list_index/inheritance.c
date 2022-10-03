
#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance list_index_expression_inheritance = {
	.print_source = list_index_expression_print_source,
	.evaluate = list_index_expression_evaluate,
	.print = list_index_expression_print,
	.free = free_list_index_expression,
};

