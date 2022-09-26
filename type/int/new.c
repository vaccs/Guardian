
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "new.h"

struct type* new_int_type()
{
	ENTER;
	
	struct type* retval = new_type(
		tk_int,
		sizeof(struct int_type));
	
	EXIT;
	return retval;
}

