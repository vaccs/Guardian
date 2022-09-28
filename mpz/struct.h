
#include <gmp.h>

struct mpz
{
	mpz_t mpz;
	unsigned refcount;
};

