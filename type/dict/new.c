
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_dict_type(
	unsigned id,
	struct type* key,
	struct type* value)
{
	ENTER;
	
	struct dict_type* this = (void*) new_type(
		id,
		tk_dict,
		&dict_type_inheritance,
		sizeof(*this));
	
	this->key = key;
	
	this->value = value;
	
	EXIT;
	return (void*) this;
}

