
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

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
		switch (current->kind)
		{
			case snk_cstring:
				fputs(current->cstring, stream);
				break;
			
			case snk_string:
				fwrite(current->string->chars, 1, current->string->len, stream);
				break;
			
			case snk_subtree:
				stringtree_stream(current->tree, stream);
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	EXIT;
}

