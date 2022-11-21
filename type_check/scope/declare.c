
#include <assert.h>

#include <stdlib.h>

#include <debug.h>

#include <avl/search.h>
#include <avl/insert.h>

#include <value/inc.h>

#include "node/struct.h"
#include "node/new.h"

#include "layer.h"
#include "struct.h"
#include "declare.h"

void type_check_scope_declare(
	struct type_check_scope* this,
	struct string* name,
	struct type* type)
{
	ENTER;
	
	assert(this->head);
	
	struct type_check_scope_node* node = new_type_check_scope_node(name, type);
	
	if (!avl_insert(this->head->tree, node))
	{
		TODO;
		exit(1);
	}
	
	EXIT;
}

void type_check_scope_declare_value(
	struct type_check_scope* this,
	struct string* name,
	struct value* value)
{
	ENTER;
	
	assert(this->head);
	
	struct avl_node_t* node = avl_search(this->head->tree, &name);
	
	if (node)
	{
		struct type_check_scope_node* element = node->item;
		
		element->value = inc_value(value);
	}
	else
	{
		TODO;
	}
	
	EXIT;
}






















