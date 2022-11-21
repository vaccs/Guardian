
#include "../inheritance.h"

#include "free.h"
#include "print_source.h"
#include "inheritance.h"

struct statement_inheritance parse_statement_inheritance = {
	.print_source = parse_statement_print_source,
	.free = free_parse_statement,
};
