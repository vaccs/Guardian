
#include <debug.h>

#include <type/generate_typedef_text.h>

#include "../type/new.h"
#include "../type/add_dep.h"

#include "node/struct.h"
#include "node/new.h"

#include "struct.h"
#include "lookup.h"

void type_lookup(
	struct type_lookup* this,
	struct type* type,
	struct type* user)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &type);
	
	if (!node)
	{
		struct stringtree* tree = new_stringtree();
		
		struct out_type* otype = new_out_type(tree);
		
		struct type_lookup_node* new = new_type_lookup_node(type, otype);
		
		avl_insert(this->tree, new);
		
		struct stringtree* text = type_generate_typedef_text(type, this);
		
		stringtree_append_tree(tree, text);
		
		if (user)
		{
			node = avl_search(this->tree, &user);
			assert(node);
			struct type_lookup_node* old = node->item;
			out_type_add_dep(old->otype, otype);
		}
		
		free_stringtree(tree);
		free_stringtree(text);
	}
	else if (user)
	{
		struct type_lookup_node* a = node->item;
		
		node = avl_search(this->tree, &user);
		assert(node);
		
		struct type_lookup_node* b = node->item;
		 
		out_type_add_dep(b->otype, a->otype);
	}
	
	EXIT;
}




















