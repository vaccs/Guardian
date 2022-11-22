
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance regex_match_expression_inheritance = {

	.print_source = regex_match_expression_print_source,
	
	.evaluate = regex_match_expression_evaluate,
	.print = regex_match_expression_print,
	.free = free_regex_match_expression,
};

