
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "add.h"

struct mpz* new_mpz_from_add(
	struct mpz* left,
	struct mpz* right)
{
	ENTER;
	
	struct mpz* this = smalloc(sizeof(*this));
	
	mpz_init(this->mpz);
	
	mpz_add(this->mpz, left->mpz, right->mpz);
	
	#ifdef DEBUGGING
	gmp_printf("%Zi + %Zi = %Zi\n", left->mpz, right->mpz, this->mpz);
	#endif
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

