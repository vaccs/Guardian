
#include "inheritance.h"
#include "compare.h"
#include "free.h"

struct value_inheritance list_value_inheritance = {
	.compare = compare_list_value,
	.free = free_list_value,
};

