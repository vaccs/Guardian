
#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "is_nonempty.h"

bool ptrset_is_nonempty(const struct ptrset* this)
{
	return !!this->tree->head;
}

