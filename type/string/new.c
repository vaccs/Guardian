
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct type* new_string_type(
	unsigned id)
{
	ENTER;
	
	struct type* retval = new_type(
		id,
		tk_string,
		&string_type_inheritance,
		sizeof(struct string_type));
	
	EXIT;
	return retval;
}

