
#include <debug.h>

#include <out/function/new.h>

#include <type/struct.h>
#include <type/list/generate_index_text.h>

#include "node/struct.h"

#include "struct.h"
#include "node/new.h"
#include "lookup_inc.h"

unsigned function_lookup_index(
	struct function_lookup* this,
	struct type* type)
{
	unsigned retval;
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &(struct function_lookup_node) {
		.kind = flnk_index,
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
		
		assert(type->kind == tk_list);
		
		struct list_type* ltype = (void*) type;
		
		struct stringtree* text = list_type_generate_index_text(ltype, retval, this);
		
		avl_insert(this->tree, new_function_lookup_node(
			flnk_index, type, retval, new_out_function(text)));
	}
	
	EXIT;
	return retval;
}



















