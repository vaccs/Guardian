
#include <debug.h>

#include <mpz/struct.h>

#include "struct.h"
#include "compare.h"

int compare_integer_value(
	const struct value* a,
	const struct value* b)
{
	ENTER;
	
	const struct integer_value *A = (void*) a;
	const struct integer_value *B = (void*) b;
	
	int cmp = mpz_cmp(A->integer->mpz, B->integer->mpz);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}

