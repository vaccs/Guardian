
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <named/type/struct.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <type_cache/get_type/int.h>
#include <type_cache/get_type/bool.h>
#include <type_cache/get_type/list.h>
#include <type_cache/get_type/float.h>
#include <type_cache/get_type/tuple.h>

#include "expression.h"
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
		type = type_cache_get_float_type(tcache);
	}
	else if (expression->character_literal)
	{
		TODO;
	}
	else if (expression->string_literal)
	{
		TODO;
	}
	else if (expression->true_literal)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->false_literal)
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
	else if (expression->len_form)
	{
		TODO;
	}
	else if (expression->float_form)
	{
		TODO;
	}
	else if (expression->paren)
	{
		if (expression->tuple)
		{
			struct type_list* subtypes = new_type_list();
			
			for (unsigned i = 0, n = expression->elements.n; i < n; i++)
			{
				struct type* subtype = determine_type_of_expression(
					expression->elements.data[i],
					tcache, grammar_types, name_to_type);
				
				type_list_append(subtypes, subtype);
			}
			
			type = type_cache_get_tuple_type(tcache, subtypes);
			
			free_type_list(subtypes);
		}
		else
		{
			type = determine_type_of_expression(
				expression->subexpression,
				tcache, grammar_types, name_to_type);
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



















