
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_grammar_types(
	const struct type* super_a,
	const struct type* super_b)
{
	const struct grammar_type *a = (void*) super_a, *b = (void*) super_b;
	ENTER;
	
	int cmp = compare_strings(a->name, b->name);
	
	EXIT;
	return cmp;
}

