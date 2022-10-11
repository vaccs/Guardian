
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct type* new_char_type(
	unsigned id)
{
	ENTER;
	
	struct type* retval = new_type(
		id,
		tk_char,
		&char_type_inheritance,
		sizeof(struct char_type));
	
	EXIT;
	return retval;
}

