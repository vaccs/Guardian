
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
	struct avl_tree_t* typed_declares,
	struct out_shared* shared)
{
	ENTER;
	
	this->init_text = new_stringtree();
	
	this->uninit_text = new_stringtree();
	
	while (quack_is_nonempty(this->todo))
	{
		struct string* name = quack_pop(this->todo);
		
		struct avl_node_t* node = avl_search(typed_declares, &name);
		
		assert(node);
		
		struct named_expression* nexpression = node->item;
		
		struct expression* expression = nexpression->expression;
		
		struct type* type = expression->type;
		
		type_queue_submit(shared->tqueue, type);
		
		unsigned type_id = type->id;
		
		stringtree_append_printf(this->init_text, ""
			"type_%u* %.*s = "
		"", type_id, name->len, name->chars);
		
		struct stringtree* text = expression_print_source(expression, shared);
		
		stringtree_append_tree(this->init_text, text);
		
		stringtree_append_printf(this->init_text, ""
			";"
		"");
		
		unsigned free_id = function_queue_submit_free(shared->fqueue, type);
		
		stringtree_append_printf(this->uninit_text, ""
			"func_%u(%.*s);"
		"", free_id, name->len, name->chars);
		
		free_stringtree(text);
	}
	
	EXIT;
}

	
	
	
	
	
	
