
#include <debug.h>

#include "../new.h"
#include "../inc.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_list_type(
	struct type* element_type)
{
	ENTER;
	
	struct list_type* this = (void*) new_type(
		tk_list,
		&list_type_inheritance,
		sizeof(*this));
	
	this->element_type = inc_type(element_type);
	
	EXIT;
	return (void*) this;
}

