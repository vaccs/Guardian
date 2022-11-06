
#include <debug.h>

#include <type/struct.h>

#include <quack/is_nonempty.h>
#include <quack/pop.h>

#include <set/ptr/contains.h>
#include <set/ptr/add.h>
#include <set/ptr/discard.h>

#include <stringtree/new.h>
#include <stringtree/prepend_printf.h>
#include <stringtree/prepend_tree.h>
#include <stringtree/free.h>

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
			stringtree_prepend_printf(text, ""
				"struct type_%u;"
			"", type->id);
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

