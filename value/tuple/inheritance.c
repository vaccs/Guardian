
#include <debug.h>

#include "inheritance.h"

#include "print_source.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance tuple_value_inheritance = {
	.print_source = tuple_value_print_source,
	
	.compare = compare_tuple_value,
	
	.print = tuple_value_print,
	.free = free_tuple_value,
};

