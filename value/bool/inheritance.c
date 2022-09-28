
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct value_inheritance bool_value_inheritance = {
	.compare = compare_bool_value,
	.free = free_bool_value,
};

