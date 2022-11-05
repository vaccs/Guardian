
#include <assert.h>

#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void zpexpressionset_discard(
	struct zpexpressionset* this,
	void* element)
{
	ENTER;
	
	avl_delete(this->tree, element);
	
	TODO;
	
	EXIT;
}
