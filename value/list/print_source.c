
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <list/value/foreach.h>

#include <type/struct.h>
#include <type/list/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	assert(super->kind == vk_list);
	
	struct list_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	assert(type->kind == tk_list);
	
	struct list_type* ltype = (void*) type;
	
	struct type* etype = ltype->element_type;
	
	type_queue_submit(shared->tqueue, type);
	
	stringtree_append_printf(tree, "({");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* list = func_%u();"
	"", type->id, new_id);
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, type);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, etype);
	
	value_list_foreach(this->elements, ({
		void runme(struct value* value)
		{
			stringtree_append_printf(tree, "{");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* element = "
			"", etype->id);
			
			struct stringtree* subtree =
				value_print_source(value, shared);
			
			stringtree_append_tree(tree, subtree);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"func_%u(list, element);"
			"", append_id);
			
			stringtree_append_printf(tree, ""
				"func_%u(element);"
			"", free_id);
			
			stringtree_append_printf(tree, "}");
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "list;");
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}













