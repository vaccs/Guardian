
#include <debug.h>

#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance len_expression_inheritance = {
	.evaluate = len_expression_evaluate,
	.print = len_expression_print,
	.free = free_len_expression,
};

