
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_set_type(
	unsigned id,
	struct type* element_type)
{
	ENTER;
	
	struct set_type* this = (void*) new_type(
		id,
		tk_set,
		&set_type_inheritance,
		sizeof(*this));
	
	this->element_type = element_type;
	
	EXIT;
	return (void*) this;
}

