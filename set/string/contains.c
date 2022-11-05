
#include <debug.h>

#include <avl/search.h>

#include "struct.h"
#include "contains.h"

bool stringset_contains(
	const struct stringset* this,
	struct string* element)
{
	return !!avl_search(this->tree, element);
}

