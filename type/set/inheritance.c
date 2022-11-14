
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_new_forward.h"
#include "generate_compare_func.h"
#include "generate_print_func.h"
#include "generate_free_func.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance set_type_inheritance = {
	.generate_typedef = set_type_generate_typedef,
	.generate_new_func = set_type_generate_new_func,
	.generate_new_forward = set_type_generate_new_forward,
	.generate_compare_func = set_type_generate_compare_func,
	.generate_print_func = set_type_generate_print_func,
	.generate_free_func = set_type_generate_free_func,
	
	.compare = compare_set_type,
	.print = set_type_print,
	.free = free_set_type,
};

