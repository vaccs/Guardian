
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct type_inheritance int_type_inheritance = {
	.compare = compare_int_types,
	
	.free = free_int_type,
};

