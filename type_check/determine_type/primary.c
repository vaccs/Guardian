
#include <stdlib.h>
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
#include <type_cache/get_type/dict.h>
#include <type_cache/get_type/list.h>
#include <type_cache/get_type/charlist.h>
#include <type_cache/get_type/set.h>
#include <type_cache/get_type/float.h>
#include <type_cache/get_type/tuple.h>

#include <type_check/scope/lookup.h>

#include "../build_type.h"

#include "expression.h"
#include "primary.h"

struct type* determine_type_of_primary_expression(
	struct zebu_primary_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
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
		type = type_cache_get_charlist_type(tcache);
	}
	else if (expression->true_literal)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->false_literal)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->identifier)
	{
		struct string* name = new_string_from_token(expression->identifier);
		
		dpvs(name);
		
		if (!type_check_scope_lookup_type(scope, name, &type))
		{
			TODO;
		}
		
		free_string(name);
	}
	else if (expression->curly)
	{
		if (expression->elements.n)
		{
			TODO;
		}
		else if (expression->emptyset)
		{
			struct type* element = build_type(tcache, expression->emptyset);
			
			type = type_cache_get_set_type(tcache, element);
		}
		else if (expression->emptykey)
		{
			struct type* key = build_type(tcache, expression->emptykey);
			struct type* value = build_type(tcache, expression->emptyvalue);
			
			type = type_cache_get_dict_type(tcache, key, value);
		}
		else
		{
			assert(expression->keyvalues.n >= 1);
			
			struct type* key_type = determine_type_of_expression(
				expression->keyvalues.data[0]->key, tcache, scope);
			struct type* value_type = determine_type_of_expression(
				expression->keyvalues.data[0]->value, tcache, scope);
			
			for (unsigned i = 1, n = expression->keyvalues.n; i < n; i++)
			{
				struct type* ktype = determine_type_of_expression(
					expression->keyvalues.data[i]->key, tcache, scope);
				struct type* vtype = determine_type_of_expression(
					expression->keyvalues.data[i]->value, tcache, scope);
				
				if (key_type != ktype || value_type != vtype)
				{
					TODO;
					exit(1);
				}
			}
			
			type = type_cache_get_dict_type(tcache, key_type, value_type);
		}
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
		if (expression->elements.n != 1 || expression->comma)
		{
			struct type_list* subtypes = new_type_list();
			
			for (unsigned i = 0, n = expression->elements.n; i < n; i++)
			{
				struct type* subtype = determine_type_of_expression(
					expression->elements.data[i], tcache, scope);
				
				type_list_append(subtypes, subtype);
			}
			
			type = type_cache_get_tuple_type(tcache, subtypes);
			
			free_type_list(subtypes);
		}
		else
		{
			type = determine_type_of_expression(
				expression->elements.data[0], tcache, scope);
		}
	}
	else if (expression->list)
	{
		if (expression->emptytype)
		{
			struct type* element_type = build_type(tcache, expression->emptytype);
			
			type = type_cache_get_list_type(tcache, element_type);
		}
		else
		{
			assert(expression->elements.n >= 1);
			
			struct type* element_type = determine_type_of_expression(
				expression->elements.data[0], tcache, scope);
			
			for (unsigned i = 1, n = expression->elements.n; i < n; i++)
			{
				struct type* type = determine_type_of_expression(
					expression->elements.data[i], tcache, scope);
				
				if (element_type != type)
				{
					TODO;
					exit(1);
				}
			}
			
			type = type_cache_get_list_type(tcache, element_type);
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}



















