
#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <type/grammar/get_field.h>

#include "primary.h"
#include "postfix.h"

struct type* determine_type_of_postfix_expression(
	struct zebu_postfix_expression* expression,
	struct type_cache* tcache,
	struct avl_tree_t* grammar_types,
	struct avl_tree_t* name_to_type)
{
	struct type* type;
	ENTER;
	
	if (expression->base)
	{
		type = determine_type_of_primary_expression(expression->base, tcache, grammar_types, name_to_type);
	}
	else
	{
		if (expression->index)
		{
			struct type* ltype_generic = determine_type_of_postfix_expression(expression->sub, tcache, grammar_types, name_to_type);
			
			if (ltype_generic->kind != tk_list)
			{
				TODO;
			}
			
			struct list_type* ltype = (void*) ltype_generic;
			
			type = ltype->element_type;
		}
		else if (expression->field)
		{
			struct type* gtype_generic = determine_type_of_postfix_expression(expression->sub, tcache, grammar_types, name_to_type);
			
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
			TODO;
		}
		else
		{
			TODO;
		}
	}
	
	EXIT;
	return type;
}





















