
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <expression/struct.h>
#include <expression/inc.h>
#include <expression/parenthesis/new.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include <list/value/new.h>

#include <list/value/free.h>

#include <value/list/new.h>

#include <list/value_pair/new.h>
#include <list/value_pair/free.h>

#include <value/dict/new.h>

#include <type_cache/get_bool_type.h>
#include <type_cache/get_dict_type.h>
#include <type_cache/get_list_type.h>

#include <value/bool/new.h>
#include <value/set/new.h>
#include <value/free.h>

#include "../expression.h"

#include "../../build_type.h"

#include "integer.h"
#include "float.h"
#include "string.h"
#include "identifier.h"

#include "set_init.h"
#include "list_init.h"
#include "dict_init.h"
#include "tuple_init.h"

#include "all_form.h"
#include "any_form.h"
#include "map_form.h"
#include "len_form.h"
#include "sum_form.h"
#include "int_form.h"
#include "float_form.h"
#include "range_form.h"
#include "isdir_form.h"
#include "filter_form.h"
#include "crossmap_form.h"
#include "isabspath_form.h"
#include "isaccessibleto_form.h"
#include "isexecutableby_form.h"

#include "primary.h"

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->integer_literal)
	{
		retval = specialize_primary_integer_expression(tcache, zexpression->integer_literal);
	}
	else if (zexpression->float_literal)
	{
		retval = specialize_primary_float_expression(tcache, zexpression->float_literal);
	}
	else if (zexpression->string_literal)
	{
		retval = specialize_primary_string_expression(tcache, zexpression->string_literal);
	}
	else if (zexpression->true_literal)
	{
		struct type* type = type_cache_get_bool_type(tcache);
		
		struct value* value = new_bool_value(type, true);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->false_literal)
	{
		struct type* type = type_cache_get_bool_type(tcache);
		
		struct value* value = new_bool_value(type, false);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->identifier)
	{
		retval = specialize_primary_identifier_expression(tcache, scope, zexpression);
	}
	else if (zexpression->curly)
	{
		if (zexpression->emptyvalue)
		{
			struct type* key = build_type(tcache, zexpression->emptykey);
			
			struct type* val = build_type(tcache, zexpression->emptyvalue);
			
			struct type* type = type_cache_get_dict_type(tcache, key, val);
			
			struct value_pair_list* list = new_value_pair_list();
			
			struct value* new = new_dict_value(type, list);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			free_value_pair_list(list);
		}
		else if (zexpression->emptyset)
		{
			struct type* etype = build_type(tcache, zexpression->emptyset);
			
			struct type* ltype = type_cache_get_list_type(tcache, etype);
			
			struct value_list* set = new_value_list();
			
			struct value* new = new_set_value(ltype, set);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			
			free_value_list(set);
		}
		else if (zexpression->elements.n)
		{
			retval = specialize_primary_set_init_expression(tcache, scope, zexpression);
		}
		else if (zexpression->keyvalues.n)
		{
			retval = specialize_primary_dict_init_expression(tcache, scope, zexpression);
		}
		else
		{
			TODO;
		}
	}
	else if (zexpression->paren)
	{
		if (zexpression->elements.n != 1 || zexpression->comma)
		{
			retval = specialize_tuple_init_expression(tcache, scope, zexpression);
		}
		else
		{
			assert(zexpression->elements.n == 1);
			
			struct expression* sub = specialize_expression(tcache,
				scope, zexpression->elements.data[0]);
			
			if (sub->kind == ek_literal)
			{
				retval = inc_expression(sub);
			}
			else
			{
				retval = new_parenthesis_expression(sub);
			}
			
			free_expression(sub);
		}
	}
	else if (zexpression->list)
	{
		if (zexpression->emptytype)
		{
			struct type* etype = build_type(tcache, zexpression->emptytype);
			
			struct type* ltype = type_cache_get_list_type(tcache, etype);
			
			struct value_list* list = new_value_list();
			
			struct value* new = new_list_value(ltype, list);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			
			free_value_list(list);
		}
		else
		{
			retval = specialize_primary_list_init_expression(tcache,
				scope, zexpression);
		}
	}
	else if (zexpression->len_form)
	{
		retval = specialize_primary_len_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->float_form)
	{
		retval = specialize_primary_float_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->int_form)
	{
		retval = specialize_primary_int_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->crossmap_form)
	{
		retval = specialize_primary_crossmap_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->map_form)
	{
		retval = specialize_primary_map_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->all_form)
	{
		retval = specialize_primary_all_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->any_form)
	{
		retval = specialize_primary_any_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->sum_form)
	{
		retval = specialize_primary_sum_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->range_form)
	{
		retval = specialize_primary_range_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->isabspath_form)
	{
		retval = specialize_primary_isabspath_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->isdir_form)
	{
		retval = specialize_primary_isdir_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->isaccessibleto_form)
	{
		retval = specialize_primary_isaccessibleto_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->isexecutableby_form)
	{
		retval = specialize_primary_isexecutableby_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->filter_form)
	{
		retval = specialize_primary_filter_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















