
#include <debug.h>

#include <named/expression/struct.h>

#include <expression/struct.h>
#include <expression/print_source.h>

#include <type/struct.h>

#include "../shared.h"
#include "../type_queue/submit.h"
#include "../function_queue/submit_free.h"

#include "struct.h"
#include "process.h"

void declare_queue_process(
	struct declare_queue* this,
	struct avl_tree_t* raw_forwards,
	struct avl_tree_t* typed_declares,
	struct out_shared* shared)
{
	ENTER;
	
	this->forward_text = new_stringtree();
	
	this->init_text = new_stringtree();
	
	this->uninit_text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct string* name = quack_pop(this->todo);
		
		dpvs(name);
		
		if (stringset_contains(this->done, name))
		{
			assert(avl_search(raw_forwards, &name));
		}
		else
		{
			struct avl_node_t* node = avl_search(typed_declares, &name);
			
			assert(node);
			
			struct named_expression* nexpression = node->item;
			
			struct expression* expression = nexpression->expression;
			
			struct type* type = expression->type;
			
			type_queue_submit(shared->tqueue, type);
			
			unsigned type_id = type->id;
			
			struct stringtree* subtext = expression_print_source(expression, shared);
			
			if (avl_search(raw_forwards, &name))
			{
				TODO;
			}
			else
			{
				stringtree_append_printf(this->init_text, ""
					"type_%u* %.*s = "
				"", type_id, name->len, name->chars);
				
				stringtree_append_tree(this->init_text, subtext);
				
				stringtree_append_printf(this->init_text, ""
					";"
				"");
			}
			
			unsigned free_id = function_queue_submit_free(shared->fqueue, type);
			
			stringtree_append_printf(this->uninit_text, ""
				"func_%u(%.*s);"
			"", free_id, name->len, name->chars);
			
			stringset_add(this->done, name);
			
			free_stringtree(subtext);
		}
	}
	
	EXIT;
}

	
	
	
	
	
	
