
#include <debug.h>

#include "struct.h"
#include "add.h"

struct mpz* new_mpz_from_multiply(
	struct mpz* left,
	struct mpz* right)
{
	ENTER;
	
	struct mpz* this = smalloc(sizeof(*this));
	
	mpz_init(this->mpz);
	
	mpz_mul(this->mpz, left->mpz, right->mpz);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}

