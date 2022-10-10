
#include <debug.h>

#include <type/generate_compare_text.h>

#include <out/function/new.h>

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "lookup_free.h"

unsigned function_lookup_compare(
	struct function_lookup* this,
	struct type* type,
	unsigned using_func_id)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct function_lookup_node) {
		.kind = flnk_compare,
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
		
		struct stringtree* text = type_generate_compare_text(type, retval, this);
		
		avl_insert(this->tree, new_function_lookup_node(
			flnk_compare, type, retval, new_out_function(text)));
	}
	
	if (using_func_id)
	{
		TODO;
	}
	
	EXIT;
	return retval;
}
