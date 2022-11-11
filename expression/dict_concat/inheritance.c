
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance dict_concat_expression_inheritance = {
	.print_source = dict_concat_expression_print_source,
	.evaluate = dict_concat_expression_evaluate,
	.print = dict_concat_expression_print,
	.free = free_dict_concat_expression,
};

