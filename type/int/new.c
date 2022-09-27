
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

struct type* new_int_type()
{
	ENTER;
	
	struct type* retval = new_type(
		tk_int,
		&int_type_inheritance,
		sizeof(struct int_type));
	
	EXIT;
	return retval;
}

