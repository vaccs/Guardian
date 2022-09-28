
#include <debug.h>

#include "node/struct.h"
#include "node/new.h"
#include "struct.h"
#include "add.h"

void unresolved_add(
	struct unresolved* this,
	struct string* name,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		struct unresolved_node* old = node->item;
		
		ptrset_add(old->usages, expression);
	}
	else
	{
		struct unresolved_node* new = new_unresolved_node(name, expression);
		
		avl_insert(this->tree, new);
	}
	
	EXIT;
}













