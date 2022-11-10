
#include <assert.h>

#include <debug.h>

/*#include <mpz/struct.h>*/

/*#include <dict/value/struct.h>*/

/*#include "../compare.h"*/

#include "struct.h"
#include "compare.h"

int compare_dict_value(
	const struct value* a,
	const struct value* b)
{
	TODO;
	#if 0
	int cmp = 0;
	ENTER;
	
	const struct dict_value* A = (const void*) a;
	const struct dict_value* B = (const void*) b;
	
	unsigned i = 0, a_n = A->elements->n, b_n = B->elements->n;
	
	while (!cmp && i < a_n && i < b_n)
	{
		struct value* ae = A->elements->data[i];
		struct value* be = B->elements->data[i];
		
		cmp = compare_values(ae, be);
		
		i++;
	}
	
	if (!cmp)
	{
		if (a_n > b_n)
			cmp = +1;
		else if (a_n < b_n)
			cmp = -1;
	}
	
	EXIT;
	return cmp;
	#endif
}














