
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance funccall_expression_inheritance = {
	.evaluate = funccall_expression_evaluate,
	.print = funccall_expression_print,
	.free = free_funccall_expression,
};

