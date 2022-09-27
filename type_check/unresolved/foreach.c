
#include <debug.h>

#include <parse/parser.h>

#include "node/struct.h"
#include "struct.h"
#include "foreach.h"

void unresolved_foreach(
	const struct unresolved* this,
	void (*runme)(struct string* name))
{
	ENTER;
	
	struct avl_node_t* current, *next = NULL;
	
	current = this->tree->head;
	
	if (current && current->next)
		next = current->next;
	
	while (current)
	{
		struct unresolved_node* node = current->item;
		
		runme(node->name);
		
		current = next;
		
		if (current && current->next)
			next = current->next;
	}
	
	EXIT;
}

void unresolved_foreach2(
	const struct unresolved* this,
	void (*runme)(struct string* name, struct type* type, struct value* value))
{
	ENTER;
	
	struct avl_node_t* current, *next = NULL;
	
	current = this->tree->head;
	
	if (current && current->next)
		next = current->next;
	
	while (current)
	{
		struct unresolved_node* node = current->item;
		
		struct zebu_primary_expression* use = ptrset_get_head(node->usages);
		
		runme(node->name, use->type, use->value);
		
		current = next;
		
		if (current && current->next)
			next = current->next;
	}
	
	EXIT;
}











