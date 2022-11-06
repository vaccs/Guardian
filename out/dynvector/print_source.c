
#include <debug.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>

#include <avl/tree.h>

#include "struct.h"
#include "print_source.h"

struct stringtree* dynvector_print_source(
	struct dynvector* this)
{
	ENTER;
	
	dpvs(this->name);
	
	struct stringtree* tree = new_stringtree();
	
	stringtree_append_printf(tree, ""
		"static const unsigned %s[%u+1] = {"
	"", this->name, this->length);
	
	for (struct avl_node_t* node = this->list->head; node; node = node->next)
	{
		struct dynvector_node* ele = node->item;
		
		stringtree_append_printf(tree, ""
			"[%u] = %u,"
		"", ele->i, ele->v);
	}
	
	stringtree_append_printf(tree, ""
		"};"
	"");
	
	EXIT;
	return tree;
}














