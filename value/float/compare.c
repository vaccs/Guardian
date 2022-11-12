
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_float_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct float_value *A = (void*) a;
	const struct float_value *B = (void*) b;
	
	int cmp;
	
	if (A->value > B->value)
		cmp = +1;
	else if (A->value < B->value)
		cmp = +1;
	else
		cmp = +0;
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

