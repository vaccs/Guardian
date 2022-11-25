
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <defines/argv0.h>

#include <parse/parse.h>

#include <type/struct.h>
#include <type/tuple/struct.h>
#include <type/print.h>

#include <list/type/new.h>
#include <list/type/extend.h>
#include <list/type/free.h>

#include <type_cache/get_type/tuple.h>

#include "multiplicative.h"
#include "additive.h"

struct type* determine_type_of_additive_expression(
	struct zebu_additive_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_multiplicative_expression(expression->base, tcache, scope);
	}
	else if (expression->left)
	{
		struct type* left = determine_type_of_additive_expression(
			expression->left, tcache, scope);
		
		struct type* right = determine_type_of_multiplicative_expression(
			expression->right, tcache, scope);
		
		if (left->kind == tk_tuple && right->kind == tk_tuple)
		{
			struct tuple_type *ltuple = (void*) left, *rtuple = (void*) right;
			
			struct type_list* subtypes = new_type_list();
			
			type_list_extend(subtypes, ltuple->subtypes);
			
			type_list_extend(subtypes, rtuple->subtypes);
			
			type = type_cache_get_tuple_type(tcache, subtypes);
			
			free_type_list(subtypes);
		}
		else
		{
			if (left != right)
			{
				TODO;
				#if 0
				puts(""), fflush(stdout);
				fprintf(stderr, ""
					"%s: incompatible types for '+' operator: ' ' and ' '!\n"
				"", argv0);
				type_print(left), printf(" + "), type_print(right), puts(")");
				exit(1);
				#endif
			}
			
			type = left;
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}















