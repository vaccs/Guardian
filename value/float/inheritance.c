
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance float_value_inheritance = {
	.print_source = float_value_print_source,
	
	.compare = compare_float_value,
	.print = float_value_print,
	.free = free_float_value,
};

