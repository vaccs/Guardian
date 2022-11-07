
#include <debug.h>

#include <list/type/inc.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_tuple_type(
	unsigned id,
	struct type_list* subtypes)
{
	ENTER;
	
	struct tuple_type* this = (void*) new_type(
		id,
		tk_tuple,
		&tuple_type_inheritance,
		sizeof(*this));
	
	this->subtypes = inc_type_list(subtypes);
	
	EXIT;
	return (void*) this;
}

