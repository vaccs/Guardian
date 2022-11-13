
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

#include <value/lambda/struct.h>
#include <value/lambda/generate_typedef.h>

#include "struct.h"
#include "process.h"

void subtype_queue_process(
	struct subtype_queue* this,
	struct type_queue* tqueue)
{
	ENTER;
	
	struct stringtree* text = new_stringtree();
	
	while (quack_is_nonempty(this->values.todo))
	{
		struct lambda_value* lvalue = quack_pop(this->values.todo);
		
		if (ptrset_contains(this->values.done, lvalue))
		{
			stringtree_prepend_printf(text, ""
				"struct subtype_%u;"
			"", lvalue->id);
		}
		else
		{
			struct stringtree* subtext = lambda_value_generate_generate_typedef(lvalue, this, tqueue);
			
			stringtree_prepend_tree(text, subtext);
			
			ptrset_add(this->values.done, lvalue);
			
			ptrset_discard(this->values.queued, lvalue);
			
			free_stringtree(subtext);
		}
	}
	
	while (quack_is_nonempty(this->expressions.todo))
	{
		struct lambda_expression* lexpression = quack_pop(this->expressions.todo);
		
		if (ptrset_contains(this->expressions.done, lexpression))
		{
			stringtree_prepend_printf(text, ""
				"struct subtype_%u;"
			"", lexpression->id);
		}
		else
		{
			struct stringtree* subtext = lambda_expression_generate_generate_typedef(lexpression, this, tqueue);
			
			stringtree_prepend_tree(text, subtext);
			
			ptrset_add(this->expressions.done, lexpression);
			
			ptrset_discard(this->expressions.queued, lexpression);
			
			free_stringtree(subtext);
		}
	}
	
	this->text = text;
	
	EXIT;
}













