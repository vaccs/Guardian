
#include <debug.h>

#include "struct.h"
#include "contains.h"

bool zpexpressionset_contains(
	const struct zpexpressionset* this,
	const void* element)
{
	return !!avl_search(this->tree, element);
}

