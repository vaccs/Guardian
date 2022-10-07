
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_tree.h>
#include <stringtree/append_printf.h>

#include <list/value/struct.h>

/*#include <out/get_type_id.h>*/

#include <type/list/struct.h>

#include "../print_source.h"

#include "struct.h"
#include "print_source.h"

struct stringtree* list_value_print_source(
	struct value* super,
	struct out_shared* shared)
{
	ENTER;
	
	TODO;
	#if 0
	struct list_value* this = (void*) super;
	
	struct stringtree* tree = new_stringtree();
	
	struct type* type = super->type;
	
	assert(type->kind == tk_list);
	
	struct list_type* ltype = (void*) type;
	
	struct type* etype = ltype->element_type;
	
	unsigned tid = out_get_type_id(shared, type);
	
	unsigned eid = out_get_type_id(shared, etype);
	
	struct value_list* elements = this->elements;
	
	stringtree_append_printf(tree, "({");
	
	unsigned n = elements->n;
	
	stringtree_append_printf(tree,
		"type_%u* data = malloc(sizeof(*data) * %lu);", eid, n);
	
	for (unsigned i = 0; i < n; i++)
	{
		struct value* element = elements->data[i];
		
		stringtree_append_printf(tree, "data[%lu] = ", i);
		
		stringtree_append_tree(tree, value_print_source(element, shared));
		
		stringtree_append_printf(tree, ";");
	}
	
	stringtree_append_printf(tree, "new_type_%u(data, %lu);", tid, n);
	
	stringtree_append_printf(tree, "})");
	
	EXIT;
	return tree;
	#endif
}













