
#include <debug.h>

#include "struct.h"
#include "new.h"

struct mpz* new_mpz_from_string(
	const char* number)
{
	ENTER;
	
	struct mpz* this = smalloc(sizeof(*this));
	
	mpz_init(this->mpz);
	
	if (mpz_set_str(this->mpz, number, 0))
	{
		TODO;
		exit(1);
	}
	
	this->refcount = 1;
	
	EXIT;
	return this;
}
