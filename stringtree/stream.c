
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include "struct.h"
#include "stream.h"

#if 0

static void helper(
	struct stringtree* this,
	FILE* stream,
	unsigned depth)
{
	for (struct stringtree_node* current = this->head;
		current; current = current->next)
	{
		switch (current->kind)
		{
			case snk_cstring:
		for (unsigned i = 0; i < depth; i++)
			printf("\t");
				fputs(current->cstring, stream);
				break;
			
			case snk_string:
		for (unsigned i = 0; i < depth; i++)
			printf("\t");
				fwrite(current->string->chars, 1, current->string->len, stream);
				break;
			
			case snk_subtree:
				helper(current->tree, stream, depth + 1);
				break;
			
			default:
				TODO;
				break;
		}
		
		printf("\n");
	}
	
}

#endif

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

