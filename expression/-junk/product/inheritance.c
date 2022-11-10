
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance product_expression_inheritance = {
	.evaluate = product_expression_evaluate,
	.print_source = product_expression_print_source,
	.print = product_expression_print,
	.free = free_product_expression,
};

