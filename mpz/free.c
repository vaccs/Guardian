
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_mpz(struct mpz* this)
{
	if (this && !--this->refcount)
	{
		mpz_clear(this->mpz);
		
		free(this);
	}
}

