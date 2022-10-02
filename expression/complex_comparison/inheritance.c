
#include "inheritance.h"

#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance complex_comparison_expression_inheritance = {
	.print_source = complex_comparison_expression_print_source,
	.evaluate = complex_comparison_expression_evaluate,
	.print = complex_comparison_expression_print,
	.free = free_complex_comparison_expression,
};

