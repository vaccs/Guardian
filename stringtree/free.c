
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_stringtree(
	struct stringtree* this)
{
	ENTER;
	
	for (struct stringtree_node* current = this->head;
		current; current = current->next)
	{
		if (current->is_branch)
			free_stringtree(current->subbranch);
		else
			free(current->string);
	}
	
	free(this);
	
	EXIT;
}

