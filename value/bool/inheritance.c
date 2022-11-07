
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance bool_value_inheritance = {
	.print_source = bool_value_print_source,
	
	.compare = compare_bool_value,
	.print = bool_value_print,
	.free = free_bool_value,
};

