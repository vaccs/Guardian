
#include <debug.h>

#include <parse/parse.h>

#include <type/inc.h>

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
		
		ptrset_foreach(ele->usages, ({
			void runme(void* ptr)
			{
				struct zebu_primary_expression* use = ptr;
				
				use->kind = kind;
				use->type = inc_type(type);
				use->value = inc_value(value);
			}
			runme;
		}));
		
		avl_delete_node(this->tree, node);
		
		this->n--;
	}
	
	EXIT;
}
















