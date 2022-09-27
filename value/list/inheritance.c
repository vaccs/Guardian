
#include "inheritance.h"

#include "free.h"

struct value_inheritance list_value_inheritance = {
	.free = free_list_value,
};

