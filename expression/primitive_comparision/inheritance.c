
#include "inheritance.h"

#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance primitive_comparision_expression_inheritance = {
	.print_source = primitive_comparision_expression_print_source,
	.evaluate = primitive_comparision_expression_evaluate,
	.print = primitive_comparision_expression_print,
	.free = free_primitive_comparision_expression,
};

