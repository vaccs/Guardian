
#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <set/zpexpression/add.h>

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
		
		zpexpressionset_add(old->layers.current, expression);
	}
	else
	{
		struct unresolved_node* new = new_unresolved_node(name, expression);
		
		avl_insert(this->tree, new);
		
		this->n++;
	}
	
	EXIT;
}













