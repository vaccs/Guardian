
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance implication_expression_inheritance = {
	.print_source = implication_expression_print_source,
	.evaluate = implication_expression_evaluate,
	.print = implication_expression_print,
	.free = free_implication_expression,
};

