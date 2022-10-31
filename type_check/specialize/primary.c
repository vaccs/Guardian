
#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <builtin/map/evaluate.h>

#include <list/expression/struct.h>
#include <list/expression/new.h>
#include <list/expression/append.h>
#include <list/expression/free.h>

#include <expression/struct.h>
#include <expression/variable/new.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/len/new.h>
#include <expression/list/new.h>
#include <expression/sum/new.h>
#include <expression/parenthesis/new.h>
#include <expression/map/new.h>
#include <expression/product/new.h>
#include <expression/free.h>

#include <type_cache/get_type/list.h>
#include <type_cache/get_type/int.h>

#include <type/lambda/struct.h>
#include <type/list/struct.h>
#include <type/print.h>
#include <type/free.h>

#include <parameter/struct.h>

#include <list/parameter/struct.h>

#include <list/type/struct.h>

#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <value/integer/new.h>
#include <value/list/new.h>
#include <value/free.h>

#include <mpz/new.h>
#include <mpz/free.h>

#include "expression.h"
#include "primary.h"

static struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer)
{
	ENTER;
	
	dpvs(integer->data);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	struct mpz* mpz = new_mpz_from_string((char*) integer->data);
	
	struct value* value = new_integer_value(type, mpz);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	free_mpz(mpz);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_identifier_expression(
	struct type_cache* tcache,
	struct zebu_primary_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->value)
	{
		retval = new_literal_expression(zexpression->value);
	}
	else
	{
		struct string* name = new_string_from_token(zexpression->identifier);
		
		retval = new_variable_expression(zexpression->type, zexpression->kind, name);
		
		free_string(name);
	}
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_list_expression(
	struct type_cache* tcache,
	struct specialize_shared* sshared,
	struct zebu_expression** raw_elements, unsigned len)
{
	ENTER;
	
	dpv(len);
	
	assert(len);
	
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
}

static struct expression* specialize_primary_len_expression(
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
	
	struct expression* list = specialize_expression(tcache, sshared, raw_arguments[0]);
	
	if (list->type->kind != tk_list)
	{
		TODO;
		exit(1);
	}
	
	if (list->kind == ek_literal)
	{
		TODO;
	}
	else
	{
		retval = new_len_expression(tcache, list);
	}
	
	free_expression(list);
	
	EXIT;
	return retval;
}

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


struct expression* specialize_primary_expression(
	struct type_cache* tcache,
	struct specialize_shared *sshared,
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
		TODO;
	}
	else if (zexpression->character_literal)
	{
		TODO;
	}
	else if (zexpression->string_literal)
	{
		TODO;
	}
	else if (zexpression->identifier)
	{
		retval = specialize_primary_identifier_expression(tcache, zexpression);
	}
	else if (zexpression->paren)
	{
		if (zexpression->tuple)
		{
			TODO;
		}
		else
		{
			struct expression* sub = specialize_expression(tcache,
				sshared,
				zexpression->elements.data[0]);
			
			retval = new_parenthesis_expression(sub);
			
			free_expression(sub);
		}
	}
	else if (zexpression->list)
	{
		retval = specialize_primary_list_expression(tcache,
			sshared,
			zexpression->elements.data, zexpression->elements.n);
	}
	else if (zexpression->len)
	{
		retval = specialize_primary_len_expression(tcache,
			sshared,
			zexpression->args.data, zexpression->args.n);
	}
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
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

















