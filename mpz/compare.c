
#include <gmp.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_mpz(
	const struct mpz* a,
	const struct mpz* b)
{
	return mpz_cmp(a->mpz, b->mpz);
}

