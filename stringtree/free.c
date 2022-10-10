
#include <debug.h>

#include "struct.h"
#include "free.h"

void free_stringtree(
	struct stringtree* this)
{
	ENTER;
	
	if (this && !--this->refcount)
	{
		struct stringtree_node* current = this->head;
		struct stringtree_node* next = NULL;
		
		if (current)
		{
			next = current->next;
		}
		
		while (current)
		{
			if (current->is_branch)
				free_stringtree(current->tree);
			else
				free(current->string);
			
			free(current);
			
			current = next;
			
			if (current)
			{
				next = current->next;
			}
		}
		
		free(this);
	}
	
	EXIT;
}

