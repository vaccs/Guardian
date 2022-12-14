
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

/*#include <type/struct.h>*/

/*#include <list/value/new.h>*/
/*#include <list/value/extend.h>*/
/*#include <list/value/free.h>*/

#include <expression/int_math/new.h>
#include <expression/int_math/run.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
/*#include <expression/tuple_concat/new.h>*/
/*#include <expression/tuple_concat/run.h>*/
#include <expression/dict_math/new.h>
#include <expression/dict_math/run.h>
#include <expression/set_math/new.h>
#include <expression/set_math/run.h>
#include <expression/list_concat/new.h>
#include <expression/list_concat/run.h>
#include <expression/string_concat/new.h>
#include <expression/string_concat/run.h>
#include <expression/float_math/new.h>
/*#include <expression/free.h>*/

/*#include <value/float/struct.h>*/
/*#include <value/float/new.h>*/

/*#include <mpz/add.h>*/
/*#include <mpz/free.h>*/

/*#include <type/tuple/struct.h>*/

#include <type_cache/get_int_type.h>
/*#include <type_cache/get_type/tuple.h>*/

#include <list/type/new.h>
#include <list/type/extend.h>
#include <list/type/free.h>

#include <type/tuple/struct.h>

#include <type_cache/get_tuple_type.h>

#include <expression/tuple_concat/run.h>
#include <expression/tuple_concat/new.h>

#include <stringtree/new.h>
#include <stringtree/append_printf.h>
#include <stringtree/append_tree.h>
#include <stringtree/free.h>
#include <stringtree/stream.h>

#include <type/print.h>

#include <value/float/new.h>
#include <value/float/struct.h>

#include <value/free.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <expression/struct.h>
#include <expression/int_math/new.h>
#include <expression/free.h>

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
			struct stringtree* tree = new_stringtree();
			
			stringtree_append_printf(tree, "%s: incompatiable types for addition: '", argv0);
			
			{
				struct stringtree* subtree = type_print2(left->type);
				stringtree_append_tree(tree, subtree);
				free_stringtree(subtree);
			}
			
			stringtree_append_printf(tree, "' and '");
			
			{
				struct stringtree* subtree = type_print2(right->type);
				stringtree_append_tree(tree, subtree);
				free_stringtree(subtree);
			}
			
			stringtree_append_printf(tree, "'!\n");
			
			stringtree_stream(tree, stderr);
			
			free_stringtree(tree);
			
			exit(1);
		}
		else switch (left->type->kind)
		{
			case tk_int:
			{
				if (all_literals)
				{
					struct literal_expression* spef_left = (void*) left;
					struct literal_expression* spef_right = (void*) right;
					
					struct int_value* left_value = (void*) spef_left->value;
					struct int_value* right_value = (void*) spef_right->value;
					
					struct type* type = type_cache_get_int_type(tcache);
					
					struct value* value;
					
					if (zexpression->add)
						value = int_math_add_run(type, left_value, right_value);
					else if (zexpression->sub)
						value = int_math_sub_run(type, left_value, right_value);
					else
					{
						TODO;
					}
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					if (zexpression->add)
						retval = new_int_math_expression(left->type, imek_add, left, right);
					else if (zexpression->sub)
						retval = new_int_math_expression(left->type, imek_subtract, left, right);
					else
					{
						TODO;
					}
				}
				break;
			}
			
			case tk_float:
			{
				if (all_literals)
				{
					struct literal_expression* leftlit = (void*) left;
					struct literal_expression* rightlit = (void*) right;
					
					struct float_value* leftfloat = (void*) leftlit->value;
					struct float_value* rightfloat = (void*) rightlit->value;
					
					__float128 result;
					
					if (zexpression->add)
						result = leftfloat->value + rightfloat->value;
					else if (zexpression->sub)
						result = leftfloat->value - rightfloat->value;
					else
					{
						TODO;
					}
					
					struct value* value = new_float_value(left->type, result);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					if (zexpression->add)
						retval = new_float_math_expression(left->type, fmek_add, left, right);
					else if (zexpression->sub)
						retval = new_float_math_expression(left->type, fmek_subtract, left, right);
					else
					{
						TODO;
					}
				}
				break;
			}
			
			case tk_string:
			{
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct string_value*  leftstring = (void*) leftlit->value;
						struct string_value* rightstring = (void*) rightlit->value;
						
						struct value* value = string_concat_run(left->type, leftstring, rightstring);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_string_concat_expression(left->type, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_list:
			{
				if (left->type != right->type)
				{
					struct stringtree* tree = new_stringtree();
					
					stringtree_append_printf(tree, "%s: incompatiable types for list concatenation: '", argv0);
					
					{
						struct stringtree* subtree = type_print2(left->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "' and '");
					{
						struct stringtree* subtree = type_print2(right->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "'!\n");
					
					stringtree_stream(tree, stderr);
					
					exit(1);
					
					free_stringtree(tree);
				}
				
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct list_value*  leftlist = (void*) leftlit->value;
						struct list_value* rightlist = (void*) rightlit->value;
						
						struct value* value = list_concat_run(left->type, leftlist, rightlist);
						
						retval = new_literal_expression(value);
						
						free_value(value);
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
						
						struct type* type = type_cache_get_tuple_type(tcache, subtypes);
						
						struct value* value = tuple_concat_run(type, ltuple, rtuple);
						
						retval = new_literal_expression(value);
						
						free_value(value);
						
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
					struct stringtree* tree = new_stringtree();
					
					stringtree_append_printf(tree, "%s: incompatiable types for dict union: '", argv0);
					
					{
						struct stringtree* subtree = type_print2(left->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "' and '");
					{
						struct stringtree* subtree = type_print2(right->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "'!\n");
					
					stringtree_stream(tree, stderr);
					
					exit(1);
					
					free_stringtree(tree);
				}
				
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct dict_value*  leftdict = (void*) leftlit->value;
						struct dict_value* rightdict = (void*) rightlit->value;
						
						struct value* value = dict_math_union_run(left->type, leftdict, rightdict);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_dict_math_expression(left->type, dmek_union, left, right);
					}
				}
				else if (zexpression->sub)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct dict_value*  leftdict = (void*) leftlit->value;
						struct dict_value* rightdict = (void*) rightlit->value;
						
						struct value* value = dict_math_difference_run(left->type, leftdict, rightdict);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_dict_math_expression(left->type, dmek_difference, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_set:
			{
				if (left->type != right->type)
				{
					struct stringtree* tree = new_stringtree();
					
					stringtree_append_printf(tree, "%s: incompatiable types for set union: '", argv0);
					
					{
						struct stringtree* subtree = type_print2(left->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "' and '");
					{
						struct stringtree* subtree = type_print2(right->type);
						stringtree_append_tree(tree, subtree);
						free_stringtree(subtree);
					}
					stringtree_append_printf(tree, "'!\n");
					
					stringtree_stream(tree, stderr);
					
					exit(1);
					
					free_stringtree(tree);
				}
				
				if (zexpression->add)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct set_value*  leftset = (void*) leftlit->value;
						struct set_value* rightset = (void*) rightlit->value;
						
						struct value* value = set_math_union_run(left->type, leftset, rightset);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_set_math_expression(left->type, smek_union, left, right);
					}
				}
				else if (zexpression->sub)
				{
					if (all_literals)
					{
						struct literal_expression* leftlit = (void*) left;
						struct literal_expression* rightlit = (void*) right;
						
						struct set_value*  leftset = (void*) leftlit->value;
						struct set_value* rightset = (void*) rightlit->value;
						
						struct value* value = set_math_difference_run(left->type, leftset, rightset);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_set_math_expression(left->type, smek_difference, left, right);
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



















