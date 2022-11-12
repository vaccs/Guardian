
#include <assert.h>

#include <debug.h>

/*#include <avl/tree.h>*/

/*#include <pair/value/struct.h>*/

/*#include "../compare.h"*/

#include <list/value_pair/compare.h>

#include "struct.h"
#include "compare.h"

int compare_dict_value(
	const struct value* a,
	const struct value* b)
{
	int cmp = 0;
	ENTER;
	
	const struct dict_value* A = (const void*) a;
	const struct dict_value* B = (const void*) b;
	
	cmp = compare_value_pair_lists(A->elements, B->elements);
	
	EXIT;
	return cmp;
	
}














