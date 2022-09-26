
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool unresolved_is_nonempty(
	const struct unresolved* this)
{
	return !!this->n;
}

