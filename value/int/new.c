
#include <assert.h>

#include <debug.h>

#include <mpz/inc.h>

#include <type/struct.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_int_value(
	struct type* type,
	struct mpz* integer)
{
	ENTER;
	
	dpv(integer);
	
	assert(type->kind == tk_int);
	
	struct int_value* this = (void*) new_value(
		type,
		vk_int,
		&int_value_inheritance,
		sizeof(*this));
	
	this->integer = inc_mpz(integer);
	
	EXIT;
	return (void*) this;
}

