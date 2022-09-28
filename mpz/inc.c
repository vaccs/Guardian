
#include <debug.h>

#include "struct.h"
#include "inc.h"

struct mpz* inc_mpz(struct mpz* this)
{
	this->refcount++;
	return this;
}


