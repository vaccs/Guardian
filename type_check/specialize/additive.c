
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <list/value/new.h>
#include <list/value/extend.h>
#include <list/value/free.h>

#include <expression/int_math/new.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/tuple_concat/new.h>
#include <expression/dict_concat/new.h>
#include <expression/list_concat/new.h>
#include <expression/float_math/new.h>
#include <expression/struct.h>
#include <expression/free.h>

#include <mpz/add.h>
#include <mpz/free.h>

#include <type/tuple/struct.h>

#include <type_cache/get_type/int.h>
#include <type_cache/get_type/tuple.h>

#include <list/type/new.h>
#include <list/type/extend.h>
#include <list/type/free.h>

#include <value/tuple/struct.h>
#include <value/tuple/new.h>
#include <value/int/struct.h>
#include <value/int/new.h>
#include <value/list/struct.h>
#include <value/list/new.h>
#include <value/dict/new.h>
#include <value/dict/assign.h>
#include <value/dict/foreach.h>
#include <value/free.h>

#include "multiplicative.h"
#include "additive.h"

struct expression* specialize_additive_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_additive_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_multiplicative_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_additive_expression(tcache, scope, zexpression->left);
		struct expression* right = specialize_multiplicative_expression(tcache, scope, zexpression->right);
		
		bool all_literals = (left->kind == ek_literal && right->kind == ek_literal);
		
		if (left->type->kind != right->type->kind)
		{
			TODO;
			exit(1);
		}
		else switch (left->type->kind)
		{
			case tk_int:
			{
				if (left->type != right->type)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					struct literal_expression* spef_left = (void*) left;
					struct literal_expression* spef_right = (void*) right;
					
					struct int_value* left_value = (void*) spef_left->value;
					struct int_value* right_value = (void*) spef_right->value;
					
					struct mpz* number;
					
					if (zexpression->add)
					{
						number = new_mpz_from_add(left_value->integer, right_value->integer);
					}
					else
					{
						TODO;
					}
					
					struct value* value = new_int_value(type_cache_get_int_type(tcache), number);
					
					retval = new_literal_expression(value);
					
					free_value(value);
					free_mpz(number);
				}
				else
				{
					if (zexpression->add)
					{
						retval = new_int_math_expression(tcache, imek_add, left, right);
					}
					else if (zexpression->sub)
					{
						retval = new_int_math_expression(tcache, imek_subtract, left, right);
					}
					else
					{
						TODO;
					}
				}
				break;
			}
			
			case tk_float:
			{
				if (left->type != right->type)
				{
					TODO;
					exit(1);
				}
				
				if (all_literals)
				{
					TODO;
				}
				else
				{
					if (zexpression->add)
					{
						retval = new_float_math_expression(tcache, fmek_add, left, right);
					}
					else if (zexpression->sub)
					{
						retval = new_float_math_expression(tcache, fmek_subtract, left, right);
					}
					else
					{
						TODO;
					}
				}
				break;
			}
			
			case tk_list:
			{
				if (left->type != right->type)
				{
					TODO;
					exit(1);
				}
				
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* spef_left = (void*) left;
						struct literal_expression* spef_right = (void*) right;
						
						struct list_value*  left_list = (void*) spef_left->value;
						struct list_value* right_list = (void*) spef_right->value;
						
						struct value_list* concat = new_value_list();
						
						value_list_extend(concat,  left_list->elements);
						value_list_extend(concat, right_list->elements);
						
						struct value* value = new_list_value(left->type, concat);
						
						retval = new_literal_expression(value);
						
						free_value(value);
						
						free_value_list(concat);
					}
					else
					{
						retval = new_list_concat_expression(left->type, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_tuple:
			{
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* spef_left = (void*) left;
						struct literal_expression* spef_right = (void*) right;
					
						struct tuple_type* ltype = (void*) left->type;
						struct tuple_type* rtype = (void*) right->type;
						
						struct type_list* subtypes = new_type_list();
						
						type_list_extend(subtypes, ltype->subtypes);
						type_list_extend(subtypes, rtype->subtypes);
						
						struct tuple_value* ltuple = (void*) spef_left->value;
						struct tuple_value* rtuple = (void*) spef_right->value;
						
						struct value_list* subvalues = new_value_list();
						
						value_list_extend(subvalues, ltuple->subvalues);
						value_list_extend(subvalues, rtuple->subvalues);
						
						struct type* type = type_cache_get_tuple_type(tcache, subtypes);
						
						struct value* value = new_tuple_value(type, subvalues);
						
						retval = new_literal_expression(value);
						
						free_value(value);
						free_value_list(subvalues);
						free_type_list(subtypes);
					}
					else
					{
						struct tuple_type* ltuple = (void*) left->type;
						struct tuple_type* rtuple = (void*) right->type;
						
						struct type_list* subtypes = new_type_list();
						
						type_list_extend(subtypes, ltuple->subtypes);
						type_list_extend(subtypes, rtuple->subtypes);
						
						struct type* type = type_cache_get_tuple_type(tcache, subtypes);
						
						retval = new_tuple_concat_expression(type, left, right);
						
						free_type_list(subtypes);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_dict:
			{
				if (left->type != right->type)
				{
					TODO;
					exit(1);
				}
			
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* spef_left = (void*) left;
						struct literal_expression* spef_right = (void*) right;
						
						struct dict_value*  left_dict = (void*) spef_left->value;
						struct dict_value* right_dict = (void*) spef_right->value;
						
						struct value* concat_value = new_dict_value(left->type);
						
						dict_value_foreach(left_dict, ({
							void runme(struct value* key, struct value* value)
							{
								dict_value_assign(concat_value, key, value);
							}
							runme;
						}));
						
						dict_value_foreach(right_dict, ({
							void runme(struct value* key, struct value* value)
							{
								dict_value_assign(concat_value, key, value);
							}
							runme;
						}));
						
						retval = new_literal_expression(concat_value);
						
						free_value(concat_value);
					}
					else
					{
						retval = new_dict_concat_expression(left->type, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			default:
				TODO;
				break;
		}
		
		free_expression(left), free_expression(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}



















