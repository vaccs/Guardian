
#include <debug.h>

#include "struct.h"
#include "stream.h"

void stringtree_stream(
	struct stringtree* this,
	FILE* stream)
{
	ENTER;
	
	for (struct stringtree_node* current = this->head;
		current; current = current->next)
	{
		if (current->is_branch)
			stringtree_stream(current->tree, stream);
		else
			fputs(current->string, stream);
	}
	
	EXIT;
}

