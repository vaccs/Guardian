
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct value_inheritance integer_value_inheritance = {
	.compare = compare_integer_value,
	.free = free_integer_value,
};

