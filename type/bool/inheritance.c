
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_new_forward.h"
#include "generate_free_func.h"
#include "compare.h"
#include "free.h"

struct type_inheritance bool_type_inheritance = {
	.compare = compare_bool_types,
	.generate_typedef = bool_type_generate_typedef,
	.generate_new_func = bool_type_generate_new_func,
	.generate_new_forward = bool_type_generate_new_forward,
	.generate_free_func = bool_type_generate_free_func,
	.free = free_bool_type,
};

