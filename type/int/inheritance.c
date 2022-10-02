
#include <debug.h>

#include "print_source.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance int_type_inheritance = {
	.print_source = int_type_print_source,
	.compare = compare_int_types,
	.print = int_type_print,
	.free = free_int_type,
};

