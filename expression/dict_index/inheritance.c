
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance dict_index_expression_inheritance = {
	.print_source = dict_index_expression_print_source,
	.evaluate = dict_index_expression_evaluate,
	.print = dict_index_expression_print,
	.free = free_dict_index_expression,
};

