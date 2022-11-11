
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_compare_func.h"
#include "generate_free_func.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance list_type_inheritance = {
	.generate_typedef = list_type_generate_typedef,
	.generate_new_func = list_type_generate_new_func,
	.generate_compare_func = list_type_generate_compare_func,
	.generate_free_func = list_type_generate_free_func,
	
	.compare = compare_list_type,
	.print = list_type_print,
	.free = free_list_type,
};

