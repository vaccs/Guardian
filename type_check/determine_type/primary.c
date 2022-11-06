
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <named/type/struct.h>

#include <type_cache/get_type/int.h>
#include <type_cache/get_type/list.h>

#include "primary.h"

struct type* determine_type_of_primary_expression(
	struct zebu_primary_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type)
{
	struct type* type;
	ENTER;
	
	if (expression->integer_literal)
	{
		type = type_cache_get_int_type(tcache);
	}
	else if (expression->float_literal)
	{
		TODO;
	}
	else if (expression->character_literal)
	{
		TODO;
	}
	else if (expression->string_literal)
	{
		TODO;
	}
	else if (expression->identifier)
	{
		struct avl_node_t* node;
		
		struct string* name = new_string_from_token(expression->identifier);
		
		dpvs(name);
		
		if ((node = avl_search(grammar_types, &name)))
		{
			struct named_type* ntype = node->item;
			
			type = type_cache_get_list_type(tcache, ntype->type);
		}
		else if ((node = avl_search(name_to_type, &name)))
		{
			struct named_type* ntype = node->item;
			
			type = ntype->type;
		}
		else
		{
			TODO;
		}
		
		free_string(name);
	}
	else if (expression->all)
	{
		TODO;
	}
	else if (expression->any)
	{
		TODO;
	}
	else if (expression->filter)
	{
		TODO;
	}
	else if (expression->len)
	{
		TODO;
	}
	else if (expression->map)
	{
		TODO;
	}
	else if (expression->max)
	{
		TODO;
	}
	else if (expression->min)
	{
		TODO;
	}
	else if (expression->product)
	{
		TODO;
	}
	else if (expression->range)
	{
		TODO;
	}
	else if (expression->reduce)
	{
		TODO;
	}
	else if (expression->sort)
	{
		TODO;
	}
	else if (expression->sum)
	{
		TODO;
	}
	else if (expression->unique)
	{
		TODO;
	}
	else if (expression->zip)
	{
		TODO;
	}
	else if (expression->paren)
	{
		if (expression->emptytype)
		{
			TODO;
		}
		else if (expression->tuple)
		{
			TODO;
		}
		else
		{
			TODO;
		}
	}
	else if (expression->list)
	{
		if (expression->emptytype)
		{
			TODO;
		}
		else
		{
			TODO;
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}



















