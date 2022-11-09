
#include <debug.h>

#include "inheritance.h"

#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_new_forward.h"
#include "generate_free_func.h"

#include "print.h"
#include "compare.h"
#include "free.h"

struct type_inheritance environment_type_inheritance = {
	.generate_typedef = environment_type_generate_typedef,
	.generate_new_func = environment_type_generate_new_func,
	.generate_new_forward = environment_type_generate_new_forward,
	.generate_free_func = environment_type_generate_free_func,
	
	.print = environment_type_print,
	.compare = compare_environment_types,
	.free = free_environment_type,
};

