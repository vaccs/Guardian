
#include <debug.h>

#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_new_forward.h"
#include "generate_compare_func.h"
#include "generate_free_func.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance float_type_inheritance = {
	.generate_typedef = float_type_generate_typedef,
	.generate_new_func = float_type_generate_new_func,
	.generate_new_forward = float_type_generate_new_forward,
	.generate_compare_func = float_type_generate_compare_func,
	.generate_free_func = float_type_generate_free_func,
	
	.compare = compare_float_types,
	.print = float_type_print,
	.free = free_float_type,
};

