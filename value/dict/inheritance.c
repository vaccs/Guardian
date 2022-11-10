
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct value_inheritance dict_value_inheritance = {
	.print_source = dict_value_print_source,
	.compare = compare_dict_value,
	.print = dict_value_print,
	.free = free_dict_value,
};

