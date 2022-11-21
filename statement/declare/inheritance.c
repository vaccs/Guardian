
#include "../inheritance.h"

#include "free.h"
#include "print_source.h"
#include "inheritance.h"

struct statement_inheritance declare_statement_inheritance = {
	.print_source = declare_statement_print_source,
	.free = free_declare_statement,
};
