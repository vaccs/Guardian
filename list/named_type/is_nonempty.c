
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool named_type_list_is_nonempty(
	const struct named_type_list* this)
{
	return !!this->n;
}

