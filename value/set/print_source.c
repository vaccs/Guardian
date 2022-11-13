
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

/*#include <set/value/foreach.h>*/
#include <list/value/struct.h>

#include <type/struct.h>
#include <type/set/struct.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>
/*#include <out/function_queue/submit_append.h>*/
/*#include <out/function_queue/submit_free.h>*/

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* set_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct set_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	type_queue_submit(shared->tqueue, type);
	
	struct set_type* stype = (void*) type;
	
	stringtree_append_printf(tree, "({");
	
	struct value_list* elements = this->elements;
	
	stringtree_append_printf(tree,
		"struct type_%u* elements = malloc(sizeof(*elements) * %u);", stype->element_type->id, elements->n);
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		struct stringtree* subtree = value_print_source(elements->data[i], shared);
		
		stringtree_append_printf(tree, "data[%u] = ", i);
		stringtree_append_tree(tree, subtree);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(subtree);
	}
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(data, %u);", new_id, elements->n);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}













