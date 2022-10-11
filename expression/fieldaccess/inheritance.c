
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "evaluate.h"
#include "print.h"
#include "free.h"

struct expression_inheritance fieldaccess_expression_inheritance = {
	.evaluate = fieldaccess_expression_evaluate,
	.print_source = fieldaccess_expression_print_source,
	.print = fieldaccess_expression_print,
	.free = free_fieldaccess_expression,
};

