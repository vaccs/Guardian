
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <avl/tree.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* dyntable_print_source(
	struct dyntable* this)
{
	ENTER;
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"static const unsigned %s[%u + 1][%u + 1] = {"
	"", this->name, this->width, this->height);
	
	for (struct avl_node_t* node = this->tree->head; node; node = node->next)
	{
		struct dyntable_node* ele = node->item;
		
		stringtree_append_printf(tree, ""
			"[%u][%u] = %u,"
		"", ele->x, ele->y, ele->v);
	}
	
	
	stringtree_append_printf(tree, ""
		"};"
	"");
	
	EXIT;
	return tree;
}







