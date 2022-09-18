
#include <debug.h>

#include "struct.h"
#include "new.h"

struct scope* new_scope(struct avl_tree_t* grammar)
{
	ENTER;
	
	struct scope* this = smalloc(sizeof(*this));
	
	
	EXIT;
	return this;
}

