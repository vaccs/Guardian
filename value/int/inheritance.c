
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance int_value_inheritance = {
	.print_source = int_value_print_source,
	.compare = compare_int_value,
	.print = int_value_print,
	.free = free_int_value,
};

