
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance parenthesis_expression_inheritance = {

	.print_source = parenthesis_expression_print_source,
	
	.evaluate = parenthesis_expression_evaluate,
	.print = parenthesis_expression_print,
	.free = free_parenthesis_expression,
};

