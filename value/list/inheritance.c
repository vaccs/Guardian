
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance list_value_inheritance = {
	.print_source = list_value_print_source,
	.compare = compare_list_value,
	.print = list_value_print,
	.free = free_list_value,
};

