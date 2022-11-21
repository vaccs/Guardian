
#include "../inheritance.h"

#include "free.h"
#include "print_source.h"
#include "inheritance.h"

struct statement_inheritance assert_statement_inheritance = {
	.print_source = assert_statement_print_source,
	.free = free_assert_statement,
};
