
#include <debug.h>

#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_free_func.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance tuple_type_inheritance = {
	.generate_typedef = tuple_type_generate_typedef,
	.generate_free_func = tuple_type_generate_free_func,
	.generate_new_func = tuple_type_generate_new_func,
	
	.compare = compare_tuple_types,
	.print = tuple_type_print,
	.free = free_tuple_type,
};

