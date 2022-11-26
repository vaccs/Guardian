
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance string_value_inheritance = {
	.print_source = string_value_print_source,
	
	.compare = compare_string_value,
	.print = string_value_print,
	.free = free_string_value,
};

