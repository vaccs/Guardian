
#include <debug.h>

#include <mpz/free.h>

#include "struct.h"
#include "free.h"

void free_integer_value(
	struct value* super)
{
	ENTER;
	
	struct integer_value* this = (void*) super;
	
	free_mpz(this->integer);
	
	EXIT;
}

