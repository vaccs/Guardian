
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "is_nonempty.h"

bool stringset_is_nonempty(
	const struct stringset* this)
{
	return !!this->tree->head;
}

