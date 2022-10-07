
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

struct type* new_bool_type(
	unsigned id)
{
	return new_type(
		id,
		tk_bool,
		&bool_type_inheritance,
		sizeof(struct bool_type));
}

