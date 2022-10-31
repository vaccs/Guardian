
#include <debug.h>

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
		enum variable_expression_kind current_kind, deeper_kind;
		
		switch (kind)
		{
			case vek_parameter:
				current_kind = vek_parameter;
				deeper_kind = vek_captured;
				break;
			
			case vek_declare:
				current_kind = vek_declare;
				deeper_kind = vek_captured;
				break;
			
			case vek_grammar_rule:
				current_kind = vek_grammar_rule;
				deeper_kind = vek_grammar_rule;
				break;
			
			default:
			{
				dpv(kind);
				TODO;
				break;
			}
		}
		
		struct unresolved_node* ele = node->item;
		
		ptrset_foreach(ele->layers.current, ({
			void runme(void* ptr)
			{
				struct zebu_primary_expression* use = ptr;
				
				use->kind = kind;
				use->type = type;
				use->value = inc_value(value);
			}
			runme;
		}));
		
		ptrset_foreach(ele->layers.deeper, ({
			void runme(void* ptr)
			{
				struct zebu_primary_expression* use = ptr;
				
				use->kind = kind;
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
















