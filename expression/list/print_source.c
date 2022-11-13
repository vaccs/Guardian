
#include <assert.h>

#include <debug.h>

#include <type/list/struct.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <type/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
#include <out/function_queue/submit_append.h>
#include <out/function_queue/submit_free.h>

#include <list/expression/foreach.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_expression_print_source(
	struct expression* super,
	struct out_shared* shared,
	struct environment_type* environment)
{
	ENTER;
	
	assert(super->kind == ek_list);
	
	struct list_expression* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	struct list_type* ltype = (void*) super->type;
	
	struct type* etype = ltype->element_type;
	
	type_queue_submit(shared->tqueue, type);
	
	stringtree_append_printf(tree, "({");
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, type);
	
	stringtree_append_printf(tree, ""
		"struct type_%u* list = func_%u();"
	"", type->id, new_id);
	
	unsigned append_id = function_queue_submit_append(shared->fqueue, type);
	
	unsigned free_id = function_queue_submit_free(shared->fqueue, etype);
	
	expression_list_foreach(this->elements, ({
		void runme(struct expression* expression)
		{
			stringtree_append_printf(tree, "{");
			
			stringtree_append_printf(tree, ""
				"struct type_%u* element = "
			"", etype->id);
			
			struct stringtree* subtree = expression_print_source(expression, shared, environment);
			
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














