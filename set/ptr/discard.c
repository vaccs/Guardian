
#include <debug.h>

#include <avl/delete.h>

#include "struct.h"
#include "discard.h"

void ptrset_discard(
	struct ptrset* this,
	void* element)
{
	ENTER;
	
	if (avl_delete(this->tree, element))
	{
		#ifdef VERBOSE
		this->n--;
		#endif
	}
	
	EXIT;
}
