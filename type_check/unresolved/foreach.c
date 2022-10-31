
#include <debug.h>

#include <parse/parse.h>

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
		dpv(current);
		dpv(next);
		
		struct unresolved_node* node = current->item;
		
		runme(node->name);
		
		current = next;
		
		if (current)
			next = current->next;
	}
	
	EXIT;
}

void unresolved_foreach2(
	const struct unresolved* this,
	void (*runme)(struct string* name, struct type* type, struct value* value))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct unresolved_node* ele = node->item;
		
		struct zebu_primary_expression* use = ptrset_is_nonempty(ele->layers.current)
			? ptrset_get_head(ele->layers.current)
			: ptrset_get_head(ele->layers.deeper);
		
		runme(ele->name, use->type, use->value);
	}
	
	EXIT;
}





























