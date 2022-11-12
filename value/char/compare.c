
#include <assert.h>

#include <debug.h>

#include <mpz/struct.h>

#include "struct.h"
#include "compare.h"

int compare_char_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct char_value *A = (void*) a;
	const struct char_value *B = (void*) b;
	
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

