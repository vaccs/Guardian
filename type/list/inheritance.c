
#include <debug.h>

#include "inheritance.h"
#include "generate_typedef_text.h"
#include "generate_new_text.h"
#include "generate_free_text.h"
#include "compare.h"
#include "free.h"

struct type_inheritance list_type_inheritance = {
	.generate_typedef_text = list_type_generate_typedef_text,
	.generate_new_text = list_type_generate_new_text,
	.generate_free_text = list_type_generate_free_text,
	.compare = compare_list_type,
	.free = free_list_type,
};

