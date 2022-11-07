
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_float_type(
	unsigned id)
{
	ENTER;
	
	struct type* retval = new_type(
		id,
		tk_float,
		&float_type_inheritance,
		sizeof(struct float_type));
	
	EXIT;
	return retval;
}

