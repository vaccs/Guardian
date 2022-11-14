
#include <debug.h>

#include "inheritance.h"

#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_new_forward.h"
#include "generate_compare_func.h"
#include "generate_print_func.h"
#include "generate_free_func.h"

#include "print.h"
#include "compare.h"
#include "free.h"

struct type_inheritance bool_type_inheritance = {
	.generate_typedef = bool_type_generate_typedef,
	.generate_new_func = bool_type_generate_new_func,
	.generate_new_forward = bool_type_generate_new_forward,
	.generate_compare_func = bool_type_generate_compare_func,
	.generate_print_func = bool_type_generate_print_func,
	.generate_free_func = bool_type_generate_free_func,
	
	.print = bool_type_print,
	.compare = compare_bool_types,
	.free = free_bool_type,
};

