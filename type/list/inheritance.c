
#include "inheritance.h"

#include "compare.h"
#include "free.h"

struct type_inheritance list_type_inheritance = {
	.compare = compare_list_type,
	.free = free_list_type,
};

