
#include <assert.h>

#include <debug.h>

/*#include <stringtree/new.h>*/
/*#include <stringtree/append_tree.h>*/
/*#include <stringtree/append_printf.h>*/
/*#include <stringtree/free.h>*/

/*#include <out/type_queue/submit.h>*/

/*#include <set/value/foreach.h>*/

/*#include <type/struct.h>*/
/*#include <type/set/struct.h>*/

/*#include <out/shared.h>*/
/*#include <out/function_queue/submit_new.h>*/
/*#include <out/function_queue/submit_append.h>*/
/*#include <out/function_queue/submit_free.h>*/

/*#include "../print_source.h"*/

#include "struct.h"
#include "print_source.h"

struct stringtree* set_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == vk_set);
	
	struct set_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	assert(type->kind == tk_set);
	
	struct set_type* ltype = (void*) type;
	
	struct type* etype = ltype->element_type;
	
	type_queue_submit(shared->tqueue, type);
	
	type_queue_submit(shared->tqueue, etype);
	
	stringtree_append_printf(tree, "({");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* set = func_%u();"
	"", type->id, new_id);
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, type);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, etype);
	
	value_set_foreach(this->elements, ({
		void runme(struct value* value)
		{
			stringtree_append_printf(tree, "({");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* element = "
			"", type->id);
			
			struct stringtree* subtree = value_print_source(value, shared, environment);
			
			stringtree_append_tree(tree, subtree);
			stringtree_append_printf(tree, ";");
			
			stringtree_append_printf(tree, ""
				"func_%u(set, element);"
			"", append_id);
			
			stringtree_append_printf(tree, ""
				"func_%u(element);"
			"", free_id);
			
			stringtree_append_printf(tree, "})");
			
			free_stringtree(subtree);
		}
		runme;
	}));
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
	#endif
}













