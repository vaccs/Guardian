
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool parameter_list_is_nonempty(
	const struct parameter_list* this)
{
	return !!this->n;
}

