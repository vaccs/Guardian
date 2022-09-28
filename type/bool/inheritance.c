
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct type_inheritance bool_type_inheritance = {
	.compare = compare_bool_types,
	
	.free = free_bool_type,
};

