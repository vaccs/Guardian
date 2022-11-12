
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <string/new.h>
#include <string/free.h>

#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/funccall/new.h>
#include <expression/funccall/run.h>
#include <expression/list_index/new.h>
#include <expression/list_index/run.h>
#include <expression/dict_index/new.h>
#include <expression/tuple_index/new.h>
#include <expression/fieldaccess/new.h>
#include <expression/free.h>

#include <type/tuple/struct.h>

#include <value/tuple/struct.h>
#include <list/expression/struct.h>

#include <list/type/struct.h>

#include <value/inc.h>

/*#include <parameter/struct.h>*/

#include <mpz/struct.h>

#include <list/value/struct.h>
#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <type/lambda/struct.h>

#include <type/print.h>
#include <type/list/struct.h>
#include <type/dict/struct.h>
#include <type/grammar/get_field.h>

#include <value/int/struct.h>
#include <value/list/struct.h>
/*#include <value/lambda/call.h>*/
/*#include <value/inc.h>*/
#include <value/free.h>

#include "expression.h"
#include "primary.h"
#include "postfix.h"

struct expression* specialize_postfix_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_postfix_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_primary_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->sub)
	{
		struct expression* sub = specialize_postfix_expression(tcache, scope, zexpression->sub);
		
		assert(sub);
		
		if (zexpression->index)
		{
			struct expression* index = specialize_expression(tcache, scope, zexpression->index);
			
			switch (sub->type->kind)
			{
				case tk_list:
				{
					struct list_type* ltype = (void*) sub->type;
					
					if (index->type->kind != tk_int)
					{
						TODO;
						exit(1);
					}
					
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						struct literal_expression* sublit = (void*) sub;
						struct literal_expression* idxlit = (void*) index;
						
						struct list_value* list = (void*) sublit->value;
						struct int_value* index = (void*) idxlit->value;
						
						struct value* value = list_index_run(ltype->element_type, list, index);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_list_index_expression(ltype->element_type, sub, index);
					}
					break;
				}
				
				case tk_dict:
				{
					struct dict_type* dtype = (void*) sub->type;
					
					if (dtype->key != index->type)
					{
						TODO;
						exit(1);
					}
					
					if (sub->kind == ek_literal && index->kind == ek_literal)
					{
						TODO;
					}
					else
					{
						retval = new_dict_index_expression(dtype->value, sub, index);
					}
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
			if (sub->type->kind != tk_grammar)
			{
				TODO;
				exit(1);
			}
			
			struct grammar_type* subtype = (void*) sub->type;
			
			struct string* fieldname = new_string_from_token(zexpression->field);
			
			struct type* fieldtype = grammar_type_get_field(subtype, fieldname);
			
			if (!fieldtype)
			{
				TODO;
				exit(1);
			}
			
			retval = new_fieldaccess_expression(fieldtype, sub, fieldname);
			
			free_string(fieldname);
		}
		else if (zexpression->tupleindex)
		{
			if (sub->type->kind != tk_tuple)
			{
				TODO;
				exit(1);
			}
			
			struct tuple_type* tupletype = (void*) sub->type;
			
			errno = 0;
			
			char* m;
			long index = strtol((char*) zexpression->tupleindex->data, &m, 0);
			
			if (errno || *m)
			{
				TODO;
				exit(1);
			}
			
			dpv(index);
			
			if (0 <= index && index < tupletype->subtypes->n)
			{
				if (sub->kind == ek_literal)
				{
					struct literal_expression* sublit = (void*) sub;
					
					struct tuple_value* tupval = (void*) sublit->value;
					
					struct value* value = inc_value(tupval->subvalues->data[index]);
					
					retval = new_literal_expression(value);
					
					free_value(value);
				}
				else
				{
					struct type* type = tupletype->subtypes->data[index];
					
					retval = new_tuple_index_expression(type, sub, index);
				}
			}
			else
			{
				TODO;
			}
		}
		else if (zexpression->call)
		{
			assert(sub->type);
			
			if (sub->type->kind != tk_lambda)
			{
				TODO;
				exit(1);
			}
			
			struct lambda_type* lambda_type = (void*) sub->type;
			
			if (lambda_type->parameters->n != zexpression->args.n)
			{
				TODO;
				exit(1);
			}
			
			struct expression_list* arguments = new_expression_list();
			
			bool all_literals = (sub->kind == ek_literal);
			
			for (unsigned i = 0, n = zexpression->args.n; i < n; i++)
			{
				struct expression* arg = specialize_expression(tcache, scope, zexpression->args.data[i]);
				
				if (arg->kind != ek_literal)
					all_literals = false;
				
				if (lambda_type->parameters->data[i] != arg->type)
				{
					printf("maia: function call with incorrect types!\n");
					printf("maia: function type:\n");
					type_print(sub->type);
					
					printf("\nmaia: %uth argument type:\n", i);
					type_print(arg->type);
					
					puts("");
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
				
				struct value* result = funccall_run(lambda, valargs);
				
				assert(lambda_type->rettype == result->type);
				
				retval = new_literal_expression(result);
				
				free_value(result);
				
				free_value_list(valargs);
			}
			else
			{
				retval = new_funccall_expression(lambda_type->rettype, sub, arguments);
			}
			
			free_expression_list(arguments);
		}
		else
		{
			TODO;
		}
		
		free_expression(sub);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}














