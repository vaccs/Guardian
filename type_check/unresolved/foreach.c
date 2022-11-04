
#include <debug.h>

#include <avl/tree_t.h>

#include <set/zpexpression/is_nonempty.h>
#include <set/zpexpression/get_head.h>

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
	void (*runme)(
		struct string* name,
		enum variable_expression_kind kind,
		bool another))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct unresolved_node* ele = node->item;
		
		struct zebu_primary_expression* use = zpexpressionset_is_nonempty(ele->layers.current)
			? zpexpressionset_get_head(ele->layers.current)
			: zpexpressionset_get_head(ele->layers.deeper);
		
		runme(ele->name, use->kind, !!node->next);
	}
	
	EXIT;
}

void unresolved_foreach3(
	const struct unresolved* this,
	void (*runme)(
		struct string* name,
		struct type* type))
{
	ENTER;
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct unresolved_node* ele = node->item;
		
		struct zebu_primary_expression* use = zpexpressionset_is_nonempty(ele->layers.current)
			? zpexpressionset_get_head(ele->layers.current)
			: zpexpressionset_get_head(ele->layers.deeper);
		
		runme(ele->name, use->type);
	}
	
	EXIT;
}





























