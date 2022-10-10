
#include <debug.h>

#include "generate_typedef_text.h"
#include "generate_free_text.h"

#include "inheritance.h"
#include "compare.h"
#include "free.h"

struct type_inheritance grammar_type_inheritance = {
	.generate_typedef_text = grammar_type_generate_typedef_text,
	.generate_free_text = grammar_type_generate_free_text,
	
	.compare = compare_grammar_types,
	.free = free_grammar_type,
};

