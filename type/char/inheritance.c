
#include <debug.h>

#include "generate_typedef.h"
#include "generate_new_func.h"
#include "generate_compare_func.h"
#include "generate_free_func.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance char_type_inheritance = {
	.generate_typedef = char_type_generate_typedef,
	.generate_new_func = char_type_generate_new_func,
	.generate_compare_func = char_type_generate_compare_func,
	.generate_free_func = char_type_generate_free_func,
	
	.compare = compare_char_types,
	.print = char_type_print,
	.free = free_char_type,
};

