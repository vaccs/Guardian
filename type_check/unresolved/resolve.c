
#include <debug.h>

#include <avl/search.h>
#include <avl/delete_node.h>

#include <set/zpexpression/foreach.h>

#include <parse/parse.h>

#include <value/inc.h>

#include "node/struct.h"
#include "struct.h"
#include "resolve.h"

void unresolved_resolve(
	struct unresolved* this,
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type,
	struct value* value)
{
	ENTER;
	
	struct avl_node_t* node = avl_search(this->tree, &name);
	
	if (node)
	{
		struct unresolved_node* ele = node->item;
		
		zpexpressionset_foreach(ele->layers.current, ({
			void runme(struct zebu_primary_expression* use)
			{
				use->kind = kind;
				use->type = type;
				use->value = inc_value(value);
			}
			runme;
		}));
		
		enum variable_expression_kind deeper_kind;
		
		if (kind == vek_forward)
			deeper_kind = kind;
		else
			deeper_kind = vek_captured;
		
		zpexpressionset_foreach(ele->layers.deeper, ({
			void runme(struct zebu_primary_expression* use)
			{
				use->kind = deeper_kind;
				use->type = type;
				use->value = inc_value(value);
			}
			runme;
		}));
		
		avl_delete_node(this->tree, node);
		
		this->n--;
	}
	
	EXIT;
}
















