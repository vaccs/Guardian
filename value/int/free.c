
#include <debug.h>

#include <mpz/free.h>

#include "struct.h"
#include "free.h"

void free_int_value(
	struct value* super)
{
	ENTER;
	
	struct int_value* this = (void*) super;
	
	free_mpz(this->integer);
	
	EXIT;
}

