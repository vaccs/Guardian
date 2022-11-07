
#include <assert.h>

#include <debug.h>

#include <mpz/struct.h>

#include "struct.h"
#include "compare.h"

int compare_float_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	TODO;
	#if 0
	const struct integer_value *A = (void*) a;
	const struct integer_value *B = (void*) b;
	
	int cmp = mpz_cmp(A->integer->mpz, B->integer->mpz);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
	#endif
}

