
#include <debug.h>

#include <out/function/new.h>

#include <type/generate_new_text.h>

#include "node/struct.h"

#include "struct.h"
#include "node/new.h"
#include "lookup_inc.h"

unsigned function_lookup_new(
	struct function_lookup* this,
	struct type* type)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct function_lookup_node) {
		.kind = flnk_new,
		.type = type,
	});
	
	if (node)
	{
		struct function_lookup_node* old = node->item;
		
		retval = old->id;
	}
	else
	{
		retval = this->next++;
		
		struct stringtree* text = type_generate_new_text(type, retval, this);
		
		avl_insert(this->tree, new_function_lookup_node(
			flnk_new, type, retval, new_out_function(text)));
	}
	
	EXIT;
	return retval;
}















