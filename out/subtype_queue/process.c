
#include <debug.h>

#include <set/ptr/contains.h>
#include <set/ptr/add.h>
#include <set/ptr/discard.h>

#include <quack/pop.h>
#include <quack/is_nonempty.h>

#include <stringtree/new.h>
#include <stringtree/prepend_tree.h>
#include <stringtree/prepend_printf.h>
#include <stringtree/free.h>

#include <expression/lambda/struct.h>
#include <expression/lambda/generate_typedef.h>

#include "struct.h"
#include "process.h"

void subtype_queue_process(
	struct subtype_queue* this,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct lambda_expression* lexpression = quack_pop(this->todo);
		
		if (ptrset_contains(this->done, lexpression))
		{
			stringtree_prepend_printf(text, ""
				"struct subtype_%u;"
			"", lexpression->id);
		}
		else
		{
			struct stringtree* subtext = lambda_expression_generate_generate_typedef(lexpression, this, tqueue);
			
			stringtree_prepend_tree(text, subtext);
			
			ptrset_add(this->done, lexpression);
			
			ptrset_discard(this->queued, lexpression);
			
			free_stringtree(subtext);
		}
	}
	
	this->text = text;
	
	EXIT;
}

