
#include <assert.h>

#include <debug.h>

#include <avl/tree.h>

#include "struct.h"
#include "get_head.h"

void* zpexpressionset_get_head(const struct zpexpressionset* this)
{
	assert(this->tree->head);
	
	return this->tree->head->item;
}

