
#include <debug.h>

#include "generate_typedef_text.h"
#include "generate_new_text.h"
#include "generate_compare_text.h"
#include "generate_free_text.h"
#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance int_type_inheritance = {
	.generate_typedef_text = int_type_generate_typedef_text,
	.generate_new_text = int_type_generate_new_text,
	.generate_compare_text = int_type_generate_compare_text,
	.generate_free_text = int_type_generate_free_text,
	
	.compare = compare_int_types,
	.print = int_type_print,
	.free = free_int_type,
};

