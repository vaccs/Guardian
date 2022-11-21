
#include "../inheritance.h"

#include "free.h"
#include "print_source.h"
#include "inheritance.h"

struct statement_inheritance print_statement_inheritance = {
	.print_source = print_statement_print_source,
	.free = free_print_statement,
};
