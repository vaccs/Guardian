
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance funccall_expression_inheritance = {
	.print_source = funccall_expression_print_source,
	.evaluate = funccall_expression_evaluate,
	.print = funccall_expression_print,
	.free = free_funccall_expression,
};

