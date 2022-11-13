
#include <debug.h>

#include <mpz/struct.h>

#include <list/value/compare.h>

#include "../compare.h"

#include "struct.h"
#include "compare.h"

int compare_list_value(
	const struct value* a,
	const struct value* b)
{
	int cmp = 0;
	ENTER;
	
	const struct list_value* A = (const void*) a;
	const struct list_value* B = (const void*) b;
	
	cmp = compare_value_lists(A->elements, B->elements);
	
	EXIT;
	
	return cmp;
}














