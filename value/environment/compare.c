
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_environment_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	TODO;
	#if 0
	const struct environment_value *A = (void*) a;
	const struct environment_value *B = (void*) b;
	
	int cmp;
	
	if (A->value > B->value)
		cmp = +1;
	else if (A->value < B->value)
		cmp = -1;
	else
		cmp = +0;
	
	dpv(cmp);
	
	EXIT;
	return cmp;
	#endif
}

