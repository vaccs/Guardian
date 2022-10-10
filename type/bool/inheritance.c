
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef_text.h"
#include "generate_new_text.h"
#include "generate_free_text.h"
#include "compare.h"
#include "free.h"

struct type_inheritance bool_type_inheritance = {
	.compare = compare_bool_types,
	.generate_typedef_text = bool_type_generate_typedef_text,
	.generate_new_text = bool_type_generate_new_text,
	.generate_free_text = bool_type_generate_free_text,
	.free = free_bool_type,
};

