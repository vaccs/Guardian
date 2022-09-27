
#include "inheritance.h"

#include "free.h"

struct value_inheritance integer_value_inheritance = {
	.free = free_integer_value,
};

