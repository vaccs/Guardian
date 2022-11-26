
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "print_source.h"
#include "print.h"
#include "free.h"

struct value_inheritance environment_value_inheritance = {
	.print_source = environment_value_print_source,
	
	.compare = compare_environment_value,
	.print = environment_value_print,
	.free = free_environment_value,
};

