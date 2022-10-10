
#include <debug.h>

#include "inheritance.h"
#include "compare.h"
#include "free.h"

struct type_inheritance grammar_type_inheritance = {
	.compare = compare_grammar_types,
	.free = free_grammar_type,
};

