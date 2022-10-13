
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance map_expression_inheritance = {
	.evaluate = map_expression_evaluate,
	.print_source = map_expression_print_source,
	.print = map_expression_print,
	.free = free_map_expression,
};

