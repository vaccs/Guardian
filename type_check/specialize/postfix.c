
#include <debug.h>

#include <parse/parser.h>

#include <type/struct.h>

#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include <list/value/new.h>

#include <list/expression/struct.h>

#include <list/parameter/struct.h>

#include <parameter/struct.h>

#include <list/value/struct.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <scope/new.h>
#include <scope/free.h>

#include <type/lambda/struct.h>

#include <value/integer/struct.h>
#include <value/list/struct.h>
#include <value/lambda/call.h>
#include <value/inc.h>
#include <value/free.h>

#include "expression.h"
#include "primary.h"
#include "postfix.h"

struct expression* specialize_postfix_expression(
	struct type_cache* tcache,
	struct zebu_postfix_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_primary_expression(tcache, zexpression->base);
	}
	else
	{
		assert(zexpression->sub);
		
		struct expression* sub = specialize_postfix_expression(tcache, zexpression->sub);
		
		if (zexpression->index)
		{
			struct expression* index = specialize_expression(tcache, zexpression->index);
			
			if (index->type->kind != tk_int)
			{
				TODO;
				exit(1);
			}
			
			switch (sub->type->kind)
			{
				case tk_list:
				{
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						struct literal_expression* spef_sub = (void*) sub;
						struct literal_expression* spef_index = (void*) index;
						
						struct list_value* list = (void*) spef_sub->value;
						struct integer_value* index = (void*) spef_index->value;
						
						if (0 <= index->integer && index->integer < list->elements->n)
						{
							struct value* element = list->elements->data[index->integer];
							
							retval = new_literal_expression(element);
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
					break;
				}
				
				case tk_tuple:
				{
					TODO;
					break;
				}
				
				default:
					TODO;
					break;
			}
			
			free_expression(index);
		}
		else if (zexpression->field)
		{
			TODO;
		}
		else if (zexpression->call)
		{
			if (sub->type->kind != tk_lambda)
			{
				TODO;
				exit(1);
			}
			
			struct lambda_type* spef = (void*) sub->type;
			
			if (spef->parameters->n != zexpression->args.n)
			{
				TODO;
			}
			
			struct expression_list* arguments = new_expression_list();
			
			bool all_literals = (sub->kind == ek_literal);
			
			for (unsigned i = 0, n = zexpression->args.n; i < n; i++)
			{
				struct expression* arg = specialize_expression(tcache, zexpression->args.data[i]);
				
				if (arg->kind != ek_literal)
					all_literals = false;
				
				if (spef->parameters->data[i]->type != arg->type)
				{
					TODO;
					exit(1);
				}
				
				expression_list_append(arguments, arg);
				
				free_expression(arg);
			}
			
			if (all_literals)
			{
				struct literal_expression* spef = (void*) sub;
				
				struct lambda_value* lambda = (void*) spef->value;
				
				struct value_list* valargs = new_value_list();
				
				for (unsigned i = 0, n = arguments->n; i < n; i++)
				{
					struct expression* element = arguments->data[i];
					
					assert(element->kind == ek_literal);
					
					struct literal_expression* le = (void*) element;
					
					value_list_append(valargs, le->value);
				}
				
				struct scope* scope = new_scope();
				
				struct value* result = lambda_value_call(lambda, scope, valargs);
				
				retval = new_literal_expression(result);
				
				free_value(result);
				
				free_value_list(valargs);
				
				free_scope(scope);
			}
			else
			{
				TODO;
			}
			
			free_expression_list(arguments);
		}
		else
		{
			TODO;
		}
		
		free_expression(sub);
	}
	
	EXIT;
	return retval;
}














