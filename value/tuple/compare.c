
#include <assert.h>

#include <debug.h>

#include <list/value/compare.h>

#include "struct.h"
#include "compare.h"

int compare_tuple_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct tuple_value *A = (void*) a;
	const struct tuple_value *B = (void*) b;
	
	int cmp = compare_value_lists(A->subvalues, B->subvalues);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

