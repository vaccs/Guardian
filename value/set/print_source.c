
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

#include <misc/value_to_id/add.h>
#include <misc/value_to_id/discard.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* set_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct set_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		struct set_type* stype = (void*) super->type;
		
		stringtree_append_printf(tree, "({");
		
		unsigned n = this->elements->n;
		
		stringtree_append_printf(tree,
			"struct type_%u** elements = malloc(sizeof(*elements) * %u);", stype->element_type->id, n);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(elements, %u);", super->type->id, value_id, new_id, n);
		
		for (unsigned i = 0; i < n; i++)
		{
			struct stringtree* subtree = value_print_source(this->elements->data[i], shared, vtoi);
			
			stringtree_append_printf(tree, "elements[%u] = ", i);
			stringtree_append_tree(tree, subtree);
			stringtree_append_printf(tree, ";");
			
			free_stringtree(subtree);
		}
		
		stringtree_append_printf(tree, "value_%u;", value_id);
		
		value_to_id_discard(vtoi, super);
	}
	else
	{
		TODO;
	}
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}













