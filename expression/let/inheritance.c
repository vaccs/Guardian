
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance let_expression_inheritance = {
	.print_source = let_expression_print_source,
	.evaluate = let_expression_evaluate,
	.print = let_expression_print,
	.free = free_let_expression,
};

