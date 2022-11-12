
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance set_value_inheritance = {
	.print_source = set_value_print_source,
	.compare = compare_set_value,
	.print = set_value_print,
	.free = free_set_value,
};

