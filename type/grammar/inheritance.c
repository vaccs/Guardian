
#include <debug.h>

#include "generate_typedef.h"
#include "generate_free_func.h"

#include "inheritance.h"
#include "compare.h"
#include "free.h"

struct type_inheritance grammar_type_inheritance = {
	.generate_typedef = grammar_type_generate_typedef,
	.generate_free_func = grammar_type_generate_free_func,
	
	.compare = compare_grammar_types,
	.free = free_grammar_type,
};

