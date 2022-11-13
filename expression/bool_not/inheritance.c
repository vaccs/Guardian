
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance bool_not_expression_inheritance = {

	.print_source = bool_not_expression_print_source,
	.evaluate = bool_not_expression_evaluate,
	.print = bool_not_expression_print,
	.free = free_bool_not_expression,
};

