
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <string/new.h>
#include <string/free.h>

#include <parse/parse.h>

#include <list/type/struct.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <type/tuple/struct.h>
#include <type/lambda/struct.h>
#include <type/grammar/get_field.h>

#include "primary.h"
#include "postfix.h"

struct type* determine_type_of_postfix_expression(
	struct zebu_postfix_expression* expression,
	struct type_cache* tcache,
	struct type_check_scope* scope)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_primary_expression(expression->base, tcache, scope);
	}
	else if (expression->sub)
	{
		if (expression->slice)
		{
			type =determine_type_of_postfix_expression(expression->sub, tcache, scope);
		}
		else if (expression->index)
		{
			struct type* ltype_generic = determine_type_of_postfix_expression(expression->sub, tcache, scope);
			
			if (ltype_generic->kind != tk_list)
			{
				TODO;
			}
			
			struct list_type* ltype = (void*) ltype_generic;
			
			type = ltype->element_type;
		}
		else if (expression->tupleindex)
		{
			char* m;
			
			unsigned long index = strtoul((char*) expression->tupleindex->data, &m, 10);
			
			struct type* ttype_generic = determine_type_of_postfix_expression(expression->sub, tcache, scope);
			
			if (ttype_generic->kind != tk_tuple)
			{
				TODO;
				exit(1);
			}
			
			struct tuple_type* ttype = (void*) ttype_generic;
			
			if (index >= ttype->subtypes->n)
			{
				TODO;
				exit(1);
			}
			
			type = ttype->subtypes->data[index];
		}
		else if (expression->field)
		{
			struct type* gtype_generic = determine_type_of_postfix_expression(expression->sub, tcache, scope);
			
			if (gtype_generic->kind != tk_grammar)
			{
				TODO;
			}
			
			struct string* field = new_string_from_token(expression->field);
			
			struct grammar_type* gtype = (void*) gtype_generic;
			
			type = grammar_type_get_field(gtype, field);
			
			if (!type)
			{
				// "grammar doesn't have taht field!"
				TODO;
			}
			
			free_string(field);
		}
		else if (expression->call)
		{
			struct type* ftype_generic = determine_type_of_postfix_expression(expression->sub, tcache, scope);
			
			if (ftype_generic->kind != tk_lambda)
			{
				TODO;
			}
			
			struct lambda_type* ftype = (void*) ftype_generic;
			
			type = ftype->rettype;
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





















