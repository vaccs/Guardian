
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <defines/argv0.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <named/type/struct.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <type/lambda/struct.h>

#include <type_cache/get_int_type.h>
#include <type_cache/get_bool_type.h>
#include <type_cache/get_dict_type.h>
#include <type_cache/get_list_type.h>
#include <type_cache/get_set_type.h>
#include <type_cache/get_string_type.h>
#include <type_cache/get_float_type.h>
#include <type_cache/get_tuple_type.h>

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
	else if (expression->string_literal)
	{
		type = type_cache_get_string_type(tcache);
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
			fprintf(stderr, "%s: use of undeclared variable '%s'!\n",
				argv0, (char*) expression->identifier->data);
			exit(1);
		}
		
		free_string(name);
	}
	else if (expression->curly)
	{
		if (expression->elements.n)
		{
			struct type* eletype = determine_type_of_expression(
				expression->elements.data[0], tcache, scope);
			
			type = type_cache_get_set_type(tcache, eletype);
		}
		else if (expression->emptyset)
		{
			TODO;
			#if 0
			struct type* element = build_type(tcache, expression->emptyset);
			
			type = type_cache_get_set_type(tcache, element);
			#endif
		}
		else if (expression->emptykey)
		{
			TODO;
			#if 0
			struct type* key = build_type(tcache, expression->emptykey);
			struct type* value = build_type(tcache, expression->emptyvalue);
			
			type = type_cache_get_dict_type(tcache, key, value);
			#endif
		}
		else if (expression->keyvalues.n >= 1)
		{
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
		else
		{
			TODO;
		}
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
			TODO;
			#if 0
			struct type* element_type = build_type(tcache, expression->emptytype);
			
			type = type_cache_get_list_type(tcache, element_type);
			#endif
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
	else if (expression->len_form)
	{
		type = type_cache_get_int_type(tcache);
	}
	else if (expression->float_form)
	{
		type = type_cache_get_float_type(tcache);
	}
	else if (expression->int_form)
	{
		type = type_cache_get_int_type(tcache);
	}
	else if (expression->crossmap_form || expression->map_form)
	{
		struct type* generic = determine_type_of_expression(expression->args.data[0], tcache, scope);
		
		if (generic->kind != tk_lambda)
		{
			TODO;
			exit(1);
		}
		
		struct lambda_type* lambda = (void*) generic;
		
		type = type_cache_get_list_type(tcache, lambda->rettype);
	}
	else if (expression->all_form)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->any_form)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->isabspath_form)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->range_form)
	{
		type = type_cache_get_list_type(tcache, type_cache_get_int_type(tcache));
	}
	else if (expression->filter_form)
	{
		assert(expression->args.n == 2);
		type = determine_type_of_expression(expression->args.data[1], tcache, scope);
	}
	else if (expression->reduce_form)
	{
		assert(expression->args.n == 3);
		type = determine_type_of_expression(expression->args.data[2], tcache, scope);
	}
	else if (expression->sum_form)
	{
		struct type* generic = determine_type_of_expression(expression->arg, tcache, scope);
		
		if (generic->kind != tk_list)
		{
			TODO;
			exit(1);
		}
		
		struct list_type* list = (void*) generic;
		
		type = list->element_type;
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}



















