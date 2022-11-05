
#include <debug.h>

#include <avl/search.h>
#include <avl/delete_node.h>

#include <set/zpexpression/foreach.h>

#include <parse/parse.h>

#include <value/inc.h>

#include "node/struct.h"
#include "struct.h"
#include "resolve.h"

void unresolved_resolve_type(
	struct unresolved* this,
	struct string* name,
	enum variable_expression_kind kind,
	struct type* type)
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
			}
			runme;
		}));
		
		enum variable_expression_kind deeper_kind;
		
		if (kind == vek_declare || kind == vek_grammar_rule)
			deeper_kind = kind;
		else
			deeper_kind = vek_captured;
		
		zpexpressionset_foreach(ele->layers.deeper, ({
			void runme(struct zebu_primary_expression* use)
			{
				use->kind = deeper_kind;
				use->type = type;
			}
			runme;
		}));
		
		this->n--;
	}
	
	EXIT;
}

void unresolved_resolve_value(
	struct unresolved* this,
	struct string* name,
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
				use->value = inc_value(value);
			}
			runme;
		}));
		
		zpexpressionset_foreach(ele->layers.deeper, ({
			void runme(struct zebu_primary_expression* use)
			{
				use->value = inc_value(value);
			}
			runme;
		}));
	}
	
	EXIT;
}
















