
#include <debug.h>

#include "generate_typedef.h"
#include "generate_free_func.h"
#include "generate_print_func.h"

#include "inheritance.h"
#include "compare.h"
#include "print.h"
#include "free.h"

struct type_inheritance grammar_type_inheritance = {
	.generate_typedef = grammar_type_generate_typedef,
	.generate_free_func = grammar_type_generate_free_func,
	.generate_print_func = grammar_type_generate_print_func,
	
	.compare = compare_grammar_types,
	.print = grammar_type_print,
	.free = free_grammar_type,
};

