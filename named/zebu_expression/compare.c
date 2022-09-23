
#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_named_zebu_expressions(const void* a, const void* b)
{
	const struct named_zebu_expression *A = a, *B = b;
	return compare_strings(A->name, B->name);
}

