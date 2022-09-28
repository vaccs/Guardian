
#include <debug.h>

#include <mpz/inc.h>

#include <type/struct.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_integer_value(
	struct type* type,
	struct mpz* integer)
{
	ENTER;
	
	dpv(integer);
	
	assert(type->kind == tk_int);
	
	struct integer_value* this = (void*) new_value(
		type,
		vk_integer,
		&integer_value_inheritance,
		sizeof(*this));
	
	this->integer = inc_mpz(integer);
	
	EXIT;
	return (void*) this;
}

