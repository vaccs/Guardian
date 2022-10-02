
#include <debug.h>

#include "inheritance.h"
#include "print_source.h"
#include "compare.h"
#include "free.h"

struct type_inheritance list_type_inheritance = {
	.print_source = list_type_print_source,
	.compare = compare_list_type,
	.free = free_list_type,
};

