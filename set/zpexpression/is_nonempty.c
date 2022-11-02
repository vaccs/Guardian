
#include <debug.h>

#include "struct.h"
#include "is_nonempty.h"

bool zpexpressionset_is_nonempty(const struct zpexpressionset* this)
{
	return !!this->tree->head;
}

