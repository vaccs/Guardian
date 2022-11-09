
/*#include <type/struct.h>*/

/*#include <builtin/map/evaluate.h>*/

/*#include <list/expression/struct.h>*/
/*#include <list/expression/new.h>*/
/*#include <list/expression/append.h>*/
/*#include <list/expression/free.h>*/

/*#include <expression/struct.h>*/
/*#include <expression/variable/new.h>*/
/*#include <expression/literal/struct.h>*/
/*#include <expression/literal/new.h>*/
/*#include <expression/len/new.h>*/
/*#include <expression/list/new.h>*/
/*#include <expression/sum/new.h>*/
/*#include <expression/parenthesis/new.h>*/
/*#include <expression/tuple/new.h>*/
/*#include <expression/map/new.h>*/
/*#include <expression/product/new.h>*/
/*#include <expression/float/new.h>*/
/*#include <expression/free.h>*/
/*#include <expression/inc.h>*/

/*#include <type_cache/get_type/list.h>*/
/*#include <type_cache/get_type/int.h>*/
/*#include <type_cache/get_type/float.h>*/
/*#include <type_cache/get_type/tuple.h>*/

/*#include <list/type/new.h>*/

/*#include <type/lambda/struct.h>*/
/*#include <type/list/struct.h>*/
/*#include <type/print.h>*/
/*#include <type/free.h>*/

/*#include <parameter/struct.h>*/

/*#include <list/parameter/struct.h>*/

/*#include <list/type/struct.h>*/
/*#include <list/type/append.h>*/
/*#include <list/type/free.h>*/

/*#include <type/tuple/struct.h>*/

/*#include <list/value/new.h>*/
/*#include <list/value/append.h>*/
/*#include <list/value/free.h>*/

/*#include <value/tuple/new.h>*/
/*#include <value/bool/new.h>*/
/*#include <value/int/new.h>*/
/*#include <value/list/new.h>*/
/*#include <value/float/new.h>*/
/*#include <value/free.h>*/

/*#include <mpz/new.h>*/
/*#include <mpz/free.h>*/

#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include <debug.h>

#include <avl/search.h>

#include <parse/parse.h>

#include <string/new.h>
#include <string/free.h>

#include <list/expression/struct.h>
#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <list/type/new.h>
#include <list/type/append.h>
#include <list/type/free.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <named/type/struct.h>

#include <named/expression/struct.h>

/*#include <type_cache/get_type/bool.h>*/
#include <type_cache/get_type/tuple.h>
#include <type_cache/get_type/list.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/tuple/new.h>
#include <expression/variable/new.h>
#include <expression/parenthesis/new.h>
#include <expression/inc.h>
#include <expression/free.h>

#include <value/int/new.h>
#include <value/bool/new.h>
#include <value/tuple/new.h>
#include <value/float/new.h>
#include <value/free.h>

#include <mpz/new.h>
#include <mpz/free.h>

#include "../scope/lookup.h"

#include "shared.h"
#include "expression.h"
#include "primary.h"

static struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer)
{
	ENTER;
	
	dpvs(integer->data);
	
	struct mpz* mpz = new_mpz_from_string((char*) integer->data);
	
	struct value* value = new_int_value(tcache, mpz);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	free_mpz(mpz);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_float_expression(
	struct type_cache* tcache,
	struct zebu_token* float_literal)
{
	ENTER;
	
	dpvs(float_literal->data);
	
	errno = 0;
	
	char* m;
	
	long double number = strtold((char*) float_literal->data, &m);
	
	if (errno || *m)
	{
		TODO;
		exit(1);
	}
	
	dpv(number);
	
	struct value* value = new_float_value(tcache, number);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_identifier_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	struct string* name = new_string_from_token(zexpression->identifier);
	
	struct type* type = NULL;
	struct value* value = NULL;
	
	if (type_check_scope_lookup(scope, name, &type, &value))
	{
		if (value)
		{
			TODO;
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
	
	free_value(value);
	
	TODO;
	#if 0
	struct avl_node_t* node = avl_search(sshared->name_to_expression, &name);
	
	if (node)
	{
		struct named_expression *nexpression = node->item;
		
		struct expression* expression = nexpression->expression;
		
		if (expression->kind == ek_literal)
		{
			retval = inc_expression(expression);
		}
		else
		{
			retval = new_variable_expression(expression->type, vek_declare, name);
		}
	}
	else if ((node = avl_search(sshared->name_to_type, &name)))
	{
		TODO;
	}
	else if ((node = avl_search(sshared->grammar_types, &name)))
	{
		struct named_type* ntype = node->item;
		
		struct type* ltype = type_cache_get_list_type(tcache, ntype->type);
		
		retval = new_variable_expression(ltype, vek_grammar_rule, name);
	}
	else
	{
		TODO;
	}
	
	free_string(name);
	
	return retval;
	#endif
}

static struct expression* specialize_tuple_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
	struct type_check_scope* scope,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	struct type_list* subtypes = new_type_list();
	
	bool all_literals = true;
	
	struct expression_list* subexpressions = new_expression_list();
	
	unsigned i, n;
	
	for (i = 0, n = zexpression->elements.n; i < n; i++)
	{
		struct expression* subexpression = specialize_expression(
			tcache, sshared, scope, zexpression->elements.data[i]);
		
		if (subexpression->kind != ek_literal)
			all_literals = false;
		
		type_list_append(subtypes, subexpression->type);
		
		expression_list_append(subexpressions, subexpression);
	}
	
	struct type* type = type_cache_get_tuple_type(tcache, subtypes);
	
	if (all_literals)
	{
		struct value_list* subvalues = new_value_list();
		
		for (i = 0; i < n; i++)
		{
			struct expression* expression = subexpressions->data[i];
			
			struct literal_expression* spef = (void*) expression;
			
			value_list_append(subvalues, spef->value);
		}
		
		struct value* value = new_tuple_value(type, subvalues);
		
		retval = new_literal_expression(value);
		
		free_value_list(subvalues);
		free_value(value);
	}
	else
	{
		retval = new_tuple_expression(type, subexpressions);
	}
	
	free_expression_list(subexpressions);
	
	free_type_list(subtypes);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_list_form_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression** raw_elements, unsigned len)
{
	ENTER;
	
	assert(len);
	
	TODO;
	#if 0
	struct type* element_type = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = len; i < n; i++)
	{
		struct expression* element = specialize_expression(tcache, sshared, raw_elements[i]);
		
		if (!element_type)
		{
			element_type = element->type;
		}
		else if (element_type != element->type)
		{
			TODO;
		}
		
		if (element->kind != ek_literal)
			all_literals = false;
		
		expression_list_append(elements, element);
		
		free_expression(element);
	}
	
	struct type* type = type_cache_get_list_type(tcache, element_type);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_list* values = new_value_list();
		
		for (unsigned i = 0, n = len; i < n; i++)
		{
			struct expression* element = elements->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(values, le->value);
		}
		
		struct value* new = new_list_value(type, values);
		
		retval = new_literal_expression(new);
		
		free_value(new);
		
		free_value_list(values);
	}
	else
	{
		retval = new_list_expression(type, elements);
	}
	
	free_expression_list(elements);
	
	EXIT;
	return retval;
	#endif
}

static struct expression* specialize_primary_len_form_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	TODO;
	#if 0
	struct expression* list = specialize_expression(tcache, sshared, raw_argument);
	
	switch (list->type->kind)
	{
		case tk_list:
		{
			if (list->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				retval = new_len_expression(tcache, list);
			}
			break;
		}
		
		case tk_tuple:
		{
			struct tuple_type* ttype = (void*) list->type;
			
			unsigned len = ttype->subtypes->n;
			
			dpv(len);
			
			struct mpz* mpz = new_mpz_from_unsigned(len);
			
			struct value* value = new_int_value(tcache, mpz);
			
			retval = new_literal_expression(value);
			
			free_value(value);
			
			free_mpz(mpz);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	free_expression(list);
	
	EXIT;
	return retval;
	#endif
}

static struct expression* specialize_primary_float_form_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	TODO;
	#if 0
	struct expression* whatever = specialize_expression(tcache, sshared, raw_argument);
	
	switch (whatever->type->kind)
	{
		case tk_float:
			retval = inc_expression(whatever);
			break;
		
		case tk_int:
			retval = new_float_expression(tcache, whatever);
			break;
		
		case tk_lambda:
		{
			// "cannot cast lambda to float!"
			TODO;
			exit(1);
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	free_expression(whatever);
	
	EXIT;
	return retval;
	#endif
}

#if 0
static struct expression* specialize_primary_sum_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	if (raw_len != 1)
	{
		TODO;
		exit(1);
	}
	
	bool all_literals = true;
	
	struct expression* list_exp = specialize_expression(tcache, sshared, raw_arguments[0]);
	
	if (list_exp->kind != ek_literal)
		all_literals = false;
	
	if (list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = ((struct list_type*) list_exp->type)->element_type;
	
	if (type->kind != tk_int && type->kind != tk_float)
	{
		TODO;
	}
	else if (all_literals)
	{
		TODO;
	}
	else
	{
		retval = new_sum_expression(type, list_exp);
	}
	
	free_expression(list_exp);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_map_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	if (raw_len < 2)
	{
		TODO;
		exit(1);
	}
	
	bool all_literals = true;
	
	struct expression* lambda_exp = specialize_expression(tcache, sshared, raw_arguments[0]);
	
	if (lambda_exp->kind != ek_literal)
		all_literals = false;
	
	if (lambda_exp->type->kind != tk_lambda)
	{
		TODO;
		exit(1);
	}
	
	struct lambda_type* lambda_type = (void*) lambda_exp->type;
	
	raw_arguments++, raw_len--;
	
	if (lambda_type->parameters->n != raw_len)
	{
		TODO;
		exit(1);
	}
	
	struct expression_list* arguments = new_expression_list();
	
	for (unsigned i = 0, n = raw_len; i < n; i++)
	{
		struct expression* arg = specialize_expression(tcache, sshared, raw_arguments[i]);
		
		if (arg->kind != ek_literal)
			all_literals = false;
		
		if (arg->type->kind != tk_list)
		{
			TODO;
			exit(1);
		}
		
		struct list_type* list_type = (void*) arg->type;
		
		if (lambda_type->parameters->data[i] != list_type->element_type)
		{
			TODO;
			exit(1);
		}
		
		expression_list_append(arguments, arg);
		
		free_expression(arg);
	}
	
	struct type* type = type_cache_get_list_type(tcache, lambda_type->rettype);
	
	if (all_literals)
	{
		TODO;
		#if 0
		struct value* lambda_val;
		struct value_list* valargs = new_value_list();
		
		{
			assert(lambda_exp->kind == ek_literal);
			
			struct literal_expression* le = (void*) lambda_exp;
			
			lambda_val = le->value;
		}
		
		for (unsigned i = 0, n = arguments->n; i < n; i++)
		{
			struct expression* element = arguments->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(valargs, le->value);
		}
		
		struct value* result = builtin_map_evaluate(type, lambda_val, valargs);
		
		retval = new_literal_expression(result);
		
		free_value(result);
		
		free_value_list(valargs);
		#endif
	}
	else
	{
		retval = new_map_expression(type, lambda_exp, arguments);
	}
	
	free_expression_list(arguments);
	
	free_expression(lambda_exp);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_product_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression** raw_arguments, unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	if (raw_len != 1)
	{
		TODO;
		exit(1);
	}
	
	bool all_literals = true;
	
	struct expression* list_exp = specialize_expression(tcache, sshared, raw_arguments[0]);
	
	if (list_exp->kind != ek_literal)
		all_literals = false;
	
	if (list_exp->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	struct type* type = ((struct list_type*) list_exp->type)->element_type;
	
	if (type->kind != tk_int && type->kind != tk_float)
	{
		TODO;
	}
	else if (all_literals)
	{
		TODO;
	}
	else
	{
		retval = new_product_expression(type, list_exp);
	}
	
	free_expression(list_exp);
	
	EXIT;
	return retval;
}
#endif

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
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
	else if (zexpression->character_literal)
	{
		TODO;
	}
	else if (zexpression->string_literal)
	{
		TODO;
	}
	else if (zexpression->true_literal)
	{
		struct value* value = new_bool_value(tcache, true);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->false_literal)
	{
		struct value* value = new_bool_value(tcache, false);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->identifier)
	{
		retval = specialize_primary_identifier_expression(tcache, scope, zexpression);
	}
	else if (zexpression->paren)
	{
		if (zexpression->tuple)
		{
			retval = specialize_tuple_expression(tcache, sshared, scope, zexpression);
		}
		else
		{
			struct expression* sub = specialize_expression(tcache,
				sshared, scope, zexpression->subexpression);
			
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
		retval = specialize_primary_list_form_expression(tcache,
			sshared,
			zexpression->elements.data, zexpression->elements.n);
	}
	else if (zexpression->len_form)
	{
		retval = specialize_primary_len_form_expression(tcache,
			sshared, zexpression->arg);
	}
	else if (zexpression->float_form)
	{
		retval = specialize_primary_float_form_expression(tcache,
			sshared, zexpression->arg);
	}
	#if 0
	else if (zexpression->sum)
	{
		retval = specialize_primary_sum_expression(tcache,
			sshared,
			zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->map)
	{
		retval = specialize_primary_map_expression(tcache,
			sshared,
			zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->product)
	{
		retval = specialize_primary_product_expression(tcache,
			sshared,
			zexpression->args.data, zexpression->args.n);
	}
	#endif
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















