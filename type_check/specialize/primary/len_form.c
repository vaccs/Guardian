
#include <assert.h>

#include <debug.h>

#include <expression/free.h>

#include <type/struct.h>

#include <expression/struct.h>

#include <type_cache/get_int_type.h>

#include <expression/len_form/new.h>

#include <expression/literal/struct.h>

#include <mpz/new.h>

#include <mpz/struct.h>

#include <list/value/struct.h>

#include <value/int/new.h>

#include <value/dict/struct.h>

#include <value/set/struct.h>

#include <list/value_pair/struct.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <value/list/struct.h>

#include <type/tuple/struct.h>

#include <list/type/struct.h>

#include <value/string/struct.h>

#include <mpz/free.h>

#include "../expression.h"

#include "len_form.h"

struct expression* specialize_primary_len_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	switch (object->type->kind)
	{
		case tk_string:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct string_value* svalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, svalue->len);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(type, object);
			}
			break;
		}
		
		case tk_list:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct list_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(type, object);
			}
			break;
		}
		
		case tk_set:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct set_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(type, object);
			}
			break;
		}
		
		case tk_dict:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct dict_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(type, object);
			}
			break;
		}
		
		case tk_tuple:
		{
			struct tuple_type* ttype = (void*) object->type;
			
			unsigned len = ttype->subtypes->n;
			
			dpv(len);
			
			struct mpz* mpz = new_mpz();
			
			mpz_set_ui(mpz->mpz, len);
			
			struct value* value = new_int_value(type, mpz);
			
			retval = new_literal_expression(value);
			
			free_value(value);
			
			free_mpz(mpz);
			break;
		}
		
		
		default:
			TODO;
			break;
	}
	
	free_expression(object);
	
	EXIT;
	return retval;
}

