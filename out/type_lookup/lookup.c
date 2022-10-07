
#include <debug.h>

#include <type/print_source.h>

#include "../type/new.h"

#include "node/new.h"

#include "struct.h"
#include "lookup.h"

void type_lookup(
	struct type_lookup* this,
	struct type* type)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &type);
	
	if (!node)
	{
		struct stringtree* text = type_print_source(type, this);
		
		struct out_type* otype = new_out_type(text);
		
		struct type_lookup_node* node = new_type_lookup_node(type, otype);
		
		avl_insert(this->tree, node);
	}
	
	EXIT;
}




















