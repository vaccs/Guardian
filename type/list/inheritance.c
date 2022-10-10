
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef_text.h"
#include "generate_free_text.h"
#include "compare.h"
#include "free.h"

struct type_inheritance list_type_inheritance = {
	.generate_free_text = list_type_generate_free_text,
	.generate_typedef_text = list_type_generate_typedef_text,
	.compare = compare_list_type,
	.free = free_list_type,
};

