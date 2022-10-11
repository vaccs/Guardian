
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool type_list_is_nonempty(
	const struct type_list* this)
{
	return !!this->n;
}

