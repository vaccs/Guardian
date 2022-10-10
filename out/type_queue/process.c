
#include <debug.h>

#include <type/generate_typedef.h>

#include "struct.h"
#include "process.h"

void type_queue_process(
	struct type_queue* this)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct type* type = quack_pop(this->todo);
		
		if (ptrset_contains(this->done, type))
		{
			TODO;
		}
		else
		{
			struct stringtree* subtext = type_generate_typedef(type, this);
			
			stringtree_prepend_tree(text, subtext);
			
			ptrset_add(this->done, type);
			
			ptrset_discard(this->queued, type);
			
			free_stringtree(subtext);
		}
	}
	
	this->text = text;
	
	EXIT;
}

