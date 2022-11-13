
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

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* dict_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	struct dict_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
/*	struct dict_type* dtype = (void*) type;*/
	
	type_queue_submit(shared->tqueue, type);
	
	stringtree_append_printf(tree, "({");
	
	struct value_pair_list* elements = this->elements;
	
	stringtree_append_printf(tree,
		"struct type_%u_pair* data = malloc(sizeof(*data) * %u);", type->id, elements->n);
	
	for (unsigned i = 0, n = elements->n; i < n; i++)
	{
		struct value_pair* element = elements->data[i];
		
		struct stringtree* key = value_print_source(element->key, shared);
		
		stringtree_append_printf(tree, "data[%u].key = ", i);
		stringtree_append_tree(tree, key);
		stringtree_append_printf(tree, ";");
		
		struct stringtree* value = value_print_source(element->value, shared);
		
		stringtree_append_printf(tree, "data[%u].value = ", i);
		stringtree_append_tree(tree, value);
		stringtree_append_printf(tree, ";");
		
		free_stringtree(key);
		free_stringtree(value);
	}
	
	unsigned new_id = function_queue_submit_new(shared->fqueue, super->type);
	
	stringtree_append_printf(tree, "func_%u(data, %u);", new_id, elements->n);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
}













