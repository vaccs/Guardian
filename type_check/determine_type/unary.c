
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <type_cache/get_bool_type.h>

#include "postfix.h"
#include "unary.h"

struct type* determine_type_of_unary_expression(
	struct zebu_unary_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_postfix_expression(expression->base, tcache, scope);
	}
	else if (expression->plus)
	{
		struct type* subtype = determine_type_of_unary_expression(expression->sub, tcache, scope);
		
		switch (subtype->kind)
		{
			case tk_int:
			case tk_float:
				type = subtype;
				break;
			
			default:
				TODO;
				break;
		}
	}
	else if (expression->minus)
	{
		struct type* subtype = determine_type_of_unary_expression(expression->sub, tcache, scope);
		
		switch (subtype->kind)
		{
			case tk_int:
			case tk_float:
				type = subtype;
				break;
			
			default:
				TODO;
				break;
		}
	}
	else if (expression->lognot)
	{
		type = type_cache_get_bool_type(tcache);
	}
	else if (expression->bitnot)
	{
		struct type* subtype = determine_type_of_unary_expression(expression->sub, tcache, scope);
		
		switch (subtype->kind)
		{
			case tk_int:
				type = subtype;
				break;
			
			default:
				TODO;
				break;
		}
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return type;
}









