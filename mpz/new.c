
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <memory/smalloc.h>

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

struct mpz* new_mpz_from_unsigned(
	unsigned number)
{
	ENTER;
	
	struct mpz* this = smalloc(sizeof(*this));
	
	mpz_init(this->mpz);
	
	mpz_set_ui(this->mpz, number);
	
	this->refcount = 1;
	
	EXIT;
	return this;
}













