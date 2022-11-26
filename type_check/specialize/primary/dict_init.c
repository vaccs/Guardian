
#include <assert.h>

#include <stdlib.h>
#include <stdbool.h>

#include <debug.h>

#include <parse/parse.h>

#include <list/expression_pair/new.h>
#include <list/expression_pair/free.h>

#include <pair/expression/new.h>
#include <pair/expression/free.h>

#include <list/value_pair/new.h>

#include <pair/value/new.h>

#include <expression/literal/struct.h>

#include <list/value_pair/append.h>

#include <pair/value/free.h>

#include <pair/expression/struct.h>

#include <list/expression_pair/struct.h>

#include <list/expression_pair/append.h>

#include <expression/struct.h>

#include <expression/free.h>

#include <expression/dict_init/run.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <list/value_pair/free.h>

#include <expression/dict_init/new.h>

#include <type_cache/get_dict_type.h>

#include "../expression.h"

#include "dict_init.h"

struct expression* specialize_primary_dict_init_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->keyvalues.n);
	
	struct type* key_type = NULL;
	struct type* val_type = NULL;
	
	struct expression_pair_list* elements = new_expression_pair_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->keyvalues.n; i < n; i++)
	{
		struct expression* key_exp = specialize_expression(
			tcache, scope, expression->keyvalues.data[i]->key);
		
		struct expression* val_exp = specialize_expression(
			tcache, scope, expression->keyvalues.data[i]->value);
		
		if (!key_type)
		{
			key_type = key_exp->type;
			val_type = val_exp->type;
		}
		else if (key_type != key_exp->type || val_type != val_exp->type)
		{
			TODO;
			exit(1);
		}
		
		if (key_exp->kind != ek_literal || val_exp->kind != ek_literal)
			all_literals = false;
		
		struct expression_pair* element = new_expression_pair(key_exp, val_exp);
		
		expression_pair_list_append(elements, element);
		
		free_expression_pair(element);
		
		free_expression(key_exp);
		free_expression(val_exp);
	}
	
	assert(key_type);
	assert(val_type);
	
	struct type* type = type_cache_get_dict_type(tcache, key_type, val_type);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_pair_list* valelements = new_value_pair_list();
		
		for (unsigned i = 0, n = expression->keyvalues.n; i < n; i++)
		{
			struct expression_pair* element = elements->data[i];
			
			struct literal_expression* keylit = (void*) element->key;
			struct literal_expression* vallit = (void*) element->value;
			
			struct value_pair* valelement = new_value_pair(keylit->value, vallit->value);
			
			value_pair_list_append(valelements, valelement);
			
			free_value_pair(valelement);
		}
		
		struct value* new = dict_init_run(type, valelements);
		
		retval = new_literal_expression(new);
		
		free_value(new);
		free_value_pair_list(valelements);
	}
	else
	{
		retval = new_dict_init_expression(type, elements);
	}
	
	free_expression_pair_list(elements);
	
	EXIT;
	return retval;
}

