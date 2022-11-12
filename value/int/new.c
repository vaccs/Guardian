
#include <assert.h>

#include <debug.h>

/*#include <type_cache/get_type/int.h>*/

#include <mpz/inc.h>

/*#include <type/struct.h>*/

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_int_value(
	struct type* type,
	struct mpz* value)
{
	ENTER;
	
	struct int_value* this = (void*) new_value(
		type,
		vk_int,
		&int_value_inheritance,
		sizeof(*this));
	
	this->value = inc_mpz(value);
	
	EXIT;
	return (void*) this;
}

