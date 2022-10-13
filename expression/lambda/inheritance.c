
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance lambda_expression_inheritance = {
	.print_source = lambda_expression_print_source,
	.evaluate = lambda_expression_evaluate,
	.print = lambda_expression_print,
	.free = free_lambda_expression,
};

