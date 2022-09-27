
#include <debug.h>

#include <type_cache/get_type/int.h>

#include <type/free.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct value* new_integer_value(
	struct type_cache* tcache,
	signed long integer)
{
	ENTER;
	
	dpv(integer);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	struct integer_value* this = (void*) new_value(
		type,
		&integer_value_inheritance,
		sizeof(*this));
	
	this->integer = integer;
	
	free_type(type);
	
	EXIT;
	return (void*) this;
}

