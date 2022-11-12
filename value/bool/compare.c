
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_bool_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct bool_value *A = (void*) a;
	const struct bool_value *B = (void*) b;
	
	int cmp;
	
	if (A->value > B->value)
		cmp = +1;
	else if (A->value < B->value)
		cmp = -1;
	else
		cmp = +0;
	
	EXIT;
	return cmp;
}

