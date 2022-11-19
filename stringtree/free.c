
#include <assert.h>

#include <stdlib.h>
#include <stddef.h>

#include <debug.h>

#include <string/free.h>

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
			switch (current->kind)
			{
				case snk_cstring:
					free(current->cstring);
					break;
				
				case snk_string:
					free_string(current->string);
					break;
				
				case snk_subtree:
					free_stringtree(current->tree);
					break;
				
				default:
					TODO;
					break;
			}
			
			free(current);
			
			current = next;
			
			if (current)
				next = current->next;
		}
		
		free(this);
	}
	
	EXIT;
}

