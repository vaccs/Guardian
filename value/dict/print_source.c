
#include <assert.h>

#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>
#include <stringtree/free.h>

#include <out/shared.h>
#include <out/type_queue/submit.h>
#include <out/function_queue/submit_new.h>

#include <type/struct.h>

#include <pair/value/struct.h>

#include <list/value_pair/struct.h>

#include <misc/value_to_id/add.h>
#include <misc/value_to_id/discard.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_value_print_source(
	struct value* super,
	struct out_shared* shared,
	struct value_to_id* vtoi)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, "({");
	
	unsigned value_id;
	if (value_to_id_add(vtoi, &value_id, super))
	{
		struct dict_value* this = (void*) super;
		
		type_queue_submit(shared->tqueue, super->type);
		
		unsigned n = this->elements->n;
		
		stringtree_append_printf(tree,
			"struct type_%u_pair* data = malloc(sizeof(*data) * %u);", super->type->id, n);
		
		unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
		stringtree_append_printf(tree,
			"struct type_%u* value_%u = func_%u(data, %u);", super->type->id, value_id, new_id, n);
		
		for (unsigned i = 0; i < n; i++)
		{
			struct value_pair* element = this->elements->data[i];
			
			struct stringtree* key = value_print_source(element->key, shared, vtoi);
			
			stringtree_append_printf(tree, "data[%u].key = ", i);
			stringtree_append_tree(tree, key);
			stringtree_append_printf(tree, ";");
			
			free_stringtree(key);
			
			struct stringtree* value = value_print_source(element->value, shared, vtoi);
			
			stringtree_append_printf(tree, "data[%u].value = ", i);
			stringtree_append_tree(tree, value);
			stringtree_append_printf(tree, ";");
			
			free_stringtree(value);
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













