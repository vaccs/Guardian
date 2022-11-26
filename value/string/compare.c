
#include <assert.h>

#include <debug.h>

#include <string.h>

#include "struct.h"
#include "compare.h"

int compare_string_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct string_value *A = (void*) a;
	const struct string_value *B = (void*) b;
	
	int cmp = memcmp(A->chars, B->chars, A->len < B->len ? A->len : B->len);
	
	if (!cmp)
	{
		if (A->len > B->len)
			cmp = +1;
		else if (A->len < B->len)
			cmp = -1;
	}
	EXIT;
	return cmp;
}

