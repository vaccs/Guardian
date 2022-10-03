
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance integer_value_inheritance = {
	.print_source = integer_value_print_source,
	.compare = compare_integer_value,
	.print = integer_value_print,
	.free = free_integer_value,
};

