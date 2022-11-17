
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

#include <expression/dict/run.h>

#include <list/expression_pair/struct.h>
#include <list/expression_pair/new.h>
#include <list/expression_pair/append.h>
#include <list/expression_pair/free.h>

#include <mpz/struct.h>

/*#include <list/value_pair/new.h>*/
/*#include <list/value_pair/append.h>*/
/*#include <list/value_pair/qsort.h>*/
/*#include <list/value_pair/free.h>*/

#include <pair/expression/struct.h>
#include <pair/expression/new.h>
#include <pair/expression/free.h>

#include <pair/value/new.h>
#include <pair/value/free.h>

#include <list/value_pair/new.h>
#include <list/value_pair/append.h>
#include <list/value_pair/free.h>

/*#include <pair/value/struct.h>*/
/*#include <pair/value/new.h>*/
/*#include <pair/value/free.h>*/

#include <named/type/struct.h>

#include <named/expression/struct.h>

#include <type_cache/get_type/bool.h>
#include <type_cache/get_type/tuple.h>
#include <type_cache/get_type/int.h>
#include <type_cache/get_type/list.h>
#include <type_cache/get_type/dict.h>
#include <type_cache/get_type/char.h>
#include <type_cache/get_type/float.h>
#include <type_cache/get_type/charlist.h>
#include <type_cache/get_type/set.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/tuple/new.h>
#include <expression/variable/new.h>
#include <expression/parenthesis/new.h>
#include <expression/float_form/new.h>
#include <expression/int_form/new.h>
#include <expression/len_form/new.h>
#include <expression/map_form/new.h>
#include <expression/map_form/run.h>
#include <expression/crossmap_form/new.h>
#include <expression/crossmap_form/run.h>
#include <expression/set/run.h>
#include <expression/dict/new.h>
#include <expression/set/new.h>
#include <expression/list/new.h>
#include <expression/inc.h>
#include <expression/free.h>

#include <type/struct.h>
#include <type/list/struct.h>
#include <type/tuple/struct.h>
#include <type/lambda/struct.h>

#include <list/type/struct.h>

#include <list/value/struct.h>

#include <list/value_pair/struct.h>

#include <value/int/new.h>
#include <value/bool/new.h>
#include <value/list/struct.h>
#include <value/list/new.h>
#include <value/char/new.h>
#include <value/tuple/new.h>
#include <value/float/new.h>
#include <value/set/struct.h>
#include <value/set/new.h>
#include <value/dict/struct.h>
#include <value/dict/new.h>
#include <value/compare.h>
#include <value/free.h>

#include <mpz/new.h>
#include <mpz/free.h>

#include "../scope/lookup.h"
#include "../build_type.h"

#include "expression.h"
#include "primary.h"

struct zebu_token;
struct zebu_expression;

static struct expression* specialize_primary_integer_expression(
	struct type_cache* tcache,
	struct zebu_token* integer)
{
	ENTER;
	
	dpvs(integer->data);
	
	struct mpz* mpz = new_mpz_from_string((char*) integer->data);
	
	struct value* value = new_int_value(type_cache_get_int_type(tcache), mpz);
	
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
	
	struct type* type = type_cache_get_float_type(tcache);
	
	struct value* value = new_float_value(type, number);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value(value);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_character_expression(
	struct type_cache* tcache,
	struct zebu_token* character_literal)
{
	struct expression* retval;
	ENTER;
	
	dpvs(character_literal->data);
	
	struct type* chartype = type_cache_get_char_type(tcache);
	
	unsigned i = 1;
	
	unsigned char code = character_literal->data[i];
	
	dpv(code);
	
	if (code == '\\')
	{
		TODO;
	}
	else
	{
		struct value* value = new_char_value(chartype, code); i++;
		
		retval = new_literal_expression(value);
	
		free_value(value);
	}
	
	if (i != character_literal->len - 1)
	{
		TODO;
	}
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_string_expression(
	struct type_cache* tcache,
	struct zebu_token* string_literal)
{
	ENTER;
	
	dpvs(string_literal->data);
	
	struct type* chartype = type_cache_get_char_type(tcache);
	
	struct type* charlist = type_cache_get_charlist_type(tcache);
	
	struct value_list* elements = new_value_list();
	
	for (unsigned i = 1, n = string_literal->len - 1; i < n; i++)
	{
		unsigned char code = string_literal->data[i];
		
		dpv(code);
		
		if (code == '\\')
		{
			TODO;
		}
		else
		{
			struct value* letter = new_char_value(chartype, code);
			
			value_list_append(elements, letter);
			
			free_value(letter);
		}
	}
	
	struct value* value = new_list_value(charlist, elements);
	
	struct expression* retval = new_literal_expression(value);
	
	free_value_list(elements);
	
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
			retval = new_literal_expression(value);
		}
		else
		{
			retval = new_variable_expression(type, name);
		}
	}
	else
	{
		TODO;
	}
	
	free_string(name);
	free_value(value);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_set_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->elements.n);
	
	struct type* eletype = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct expression* eleexp = specialize_expression(
			tcache, scope, expression->elements.data[i]);
		
		if (!eletype)
		{
			eletype = eleexp->type;
		}
		else if (eletype != eleexp->type)
		{
			TODO;
		}
		
		if (eleexp->kind != ek_literal)
			all_literals = false;
		
		expression_list_append(elements, eleexp);
		
		free_expression(eleexp);
	}
	
	assert(eletype);
	
	struct type* type = type_cache_get_set_type(tcache, eletype);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_list* values = new_value_list();
		
		for (unsigned i = 0, n = expression->elements.n; i < n; i++)
		{
			struct expression* element = elements->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(values, le->value);
		}
		
		struct value* value = set_run(type, values);
		
		retval = new_literal_expression(value);
		
		free_value(value);
		
		free_value_list(values);
	}
	else
	{
		retval = new_set_expression(type, elements);
	}
	
	free_expression_list(elements);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_dict_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->keyvalues.n);
	
	struct type* key_type = NULL;
	struct type* val_type = NULL;
	
	struct expression_pair_list* elements = new_expression_pair_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->keyvalues.n; i < n; i++)
	{
		struct expression* key_exp = specialize_expression(
			tcache, scope, expression->keyvalues.data[i]->key);
		
		struct expression* val_exp = specialize_expression(
			tcache, scope, expression->keyvalues.data[i]->value);
		
		if (!key_type)
		{
			key_type = key_exp->type;
			val_type = val_exp->type;
		}
		else if (key_type != key_exp->type || val_type != val_exp->type)
		{
			TODO;
		}
		
		if (key_exp->kind != ek_literal || val_exp->kind != ek_literal)
			all_literals = false;
		
		struct expression_pair* element = new_expression_pair(key_exp, val_exp);
		
		expression_pair_list_append(elements, element);
		
		free_expression_pair(element);
		
		free_expression(key_exp);
		free_expression(val_exp);
	}
	
	assert(key_type);
	assert(val_type);
	
	struct type* type = type_cache_get_dict_type(tcache, key_type, val_type);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_pair_list* valelements = new_value_pair_list();
		
		for (unsigned i = 0, n = expression->keyvalues.n; i < n; i++)
		{
			struct expression_pair* element = elements->data[i];
			
			struct literal_expression* keylit = (void*) element->key;
			struct literal_expression* vallit = (void*) element->value;
			
			struct value_pair* valelement = new_value_pair(keylit->value, vallit->value);
			
			value_pair_list_append(valelements, valelement);
			
			free_value_pair(valelement);
		}
		
		struct value* new = dict_run(type, valelements);
		
		retval = new_literal_expression(new);
		
		free_value(new);
		free_value_pair_list(valelements);
	}
	else
	{
		retval = new_dict_expression(type, elements);
	}
	
	free_expression_pair_list(elements);
	
	EXIT;
	return retval;
}

static struct expression* specialize_tuple_expression(
	struct type_cache* tcache,
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
			tcache, scope, zexpression->elements.data[i]);
		
		if (subexpression->kind != ek_literal)
			all_literals = false;
		
		type_list_append(subtypes, subexpression->type);
		
		expression_list_append(subexpressions, subexpression);
		
		free_expression(subexpression);
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

static struct expression* specialize_primary_list_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_primary_expression* expression)
{
	ENTER;
	
	assert(expression->elements.n);
	
	struct type* element_type = NULL;
	
	struct expression_list* elements = new_expression_list();
	
	bool all_literals = true;
	
	for (unsigned i = 0, n = expression->elements.n; i < n; i++)
	{
		struct expression* element = specialize_expression(
			tcache, scope, expression->elements.data[i]);
		
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
	
	assert(element_type);
	
	struct type* type = type_cache_get_list_type(tcache, element_type);
	
	struct expression* retval;
	
	if (all_literals)
	{
		struct value_list* values = new_value_list();
		
		for (unsigned i = 0, n = expression->elements.n; i < n; i++)
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

static struct expression* specialize_primary_len_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	switch (object->type->kind)
	{
		case tk_list:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct list_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(tcache, object);
			}
			break;
		}
		
		case tk_set:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct set_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(tcache, object);
			}
			break;
		}
		
		case tk_dict:
		{
			if (object->kind == ek_literal)
			{
				struct literal_expression* objlit = (void*) object;
				
				struct dict_value* lvalue = (void*) objlit->value;
				
				struct mpz* mpz = new_mpz();
				
				mpz_set_ui(mpz->mpz, lvalue->elements->n);
				
				struct value* value = new_int_value(type, mpz);
				
				retval = new_literal_expression(value);
				
				free_mpz(mpz);
				
				free_value(value);
			}
			else
			{
				retval = new_len_form_expression(tcache, object);
			}
			break;
		}
		
		case tk_tuple:
		{
			struct tuple_type* ttype = (void*) object->type;
			
			unsigned len = ttype->subtypes->n;
			
			dpv(len);
			
			struct mpz* mpz = new_mpz();
			
			mpz_set_ui(mpz->mpz, len);
			
			struct value* value = new_int_value(type, mpz);
			
			retval = new_literal_expression(value);
			
			free_value(value);
			
			free_mpz(mpz);
			break;
		}
		
		
		default:
			TODO;
			break;
	}
	
	free_expression(object);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_float_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	switch (object->type->kind)
	{
		case tk_float:
			retval = inc_expression(object);
			break;
		
		case tk_int:
		{
			if (object->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				struct type* type = type_cache_get_float_type(tcache);
				retval = new_float_form_expression(type, object);
			}
			break;
		}
		
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
	
	free_expression(object);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_int_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression* raw_argument)
{
	struct expression* retval;
	ENTER;
	
	struct expression* object = specialize_expression(tcache, scope, raw_argument);
	
	struct type* type = type_cache_get_int_type(tcache);
	
	switch (object->type->kind)
	{
		case tk_int:
			retval = inc_expression(object);
			break;
		
		case tk_float:
		{
			if (object->kind == ek_literal)
			{
				TODO;
			}
			else
			{
				TODO;
				#if 0
				retval = new_float_form_expression(type, object);
				#endif
			}
			break;
		}
		
		case tk_list:
		{
			struct list_type* ltype = (void*) object->type;
			if (ltype->element_type->kind == tk_char)
			{
				retval = new_int_form_expression(type, object);
			}
			else
			{
				TODO;
			}
			break;
		}
		
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
	
	free_expression(object);
	
	EXIT;
	return retval;
}

#if 0
static struct expression* specialize_primary_sum_expression(
	struct type_cache* tcache,
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
	
	struct expression* list_exp = specialize_expression(tcache, raw_arguments[0]);
	
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
#endif

static struct expression* specialize_primary_crossmap_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len >= 2);
	
	bool all_literals = true;
	
	struct expression* lambda_exp = specialize_expression(tcache, scope, raw_arguments[0]);
	
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
		struct expression* arg = specialize_expression(tcache, scope, raw_arguments[i]);
		
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
		struct literal_expression* le = (void*) lambda_exp;
		
		struct lambda_value* lambda = (void*) le->value;
		
		struct value_list* valargs = new_value_list();
		
		for (unsigned i = 0, n = arguments->n; i < n; i++)
		{
			struct expression* element = arguments->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(valargs, le->value);
		}
		
		struct value* result = crossmap_form_run(type, lambda, valargs);
		
		retval = new_literal_expression(result);
		
		free_value(result);
		
		free_value_list(valargs);
	}
	else
	{
		retval = new_crossmap_form_expression(type, lambda_exp, arguments);
	}
	
	free_expression_list(arguments);
	
	free_expression(lambda_exp);
	
	EXIT;
	return retval;
}

static struct expression* specialize_primary_map_form_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_expression** raw_arguments,
	unsigned raw_len)
{
	struct expression* retval;
	ENTER;
	
	assert(raw_len >= 2);
	
	bool all_literals = true;
	
	struct expression* lambda_exp = specialize_expression(tcache, scope, raw_arguments[0]);
	
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
		struct expression* arg = specialize_expression(tcache, scope, raw_arguments[i]);
		
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
		struct literal_expression* le = (void*) lambda_exp;
		
		struct lambda_value* lambda = (void*) le->value;
		
		struct value_list* valargs = new_value_list();
		
		for (unsigned i = 0, n = arguments->n; i < n; i++)
		{
			struct expression* element = arguments->data[i];
			
			assert(element->kind == ek_literal);
			
			struct literal_expression* le = (void*) element;
			
			value_list_append(valargs, le->value);
		}
		
		struct value* result = map_form_run(type, lambda, valargs);
		
		retval = new_literal_expression(result);
		
		free_value(result);
		
		free_value_list(valargs);
		#endif
	}
	else
	{
		retval = new_map_form_expression(type, lambda_exp, arguments);
	}
	
	free_expression_list(arguments);
	
	free_expression(lambda_exp);
	
	EXIT;
	return retval;
}

struct expression* specialize_primary_expression(
	struct type_cache* tcache,
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
		retval = specialize_primary_character_expression(tcache, zexpression->character_literal);
	}
	else if (zexpression->string_literal)
	{
		retval = specialize_primary_string_expression(tcache, zexpression->string_literal);
	}
	else if (zexpression->true_literal)
	{
		struct type* type = type_cache_get_bool_type(tcache);
		
		struct value* value = new_bool_value(type, true);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->false_literal)
	{
		struct type* type = type_cache_get_bool_type(tcache);
		
		struct value* value = new_bool_value(type, false);
		
		retval = new_literal_expression(value);
		
		free_value(value);
	}
	else if (zexpression->identifier)
	{
		retval = specialize_primary_identifier_expression(tcache, scope, zexpression);
	}
	else if (zexpression->curly)
	{
		if (zexpression->emptyvalue)
		{
			struct type* key = build_type(tcache, zexpression->emptykey);
			
			struct type* val = build_type(tcache, zexpression->emptyvalue);
			
			struct type* type = type_cache_get_dict_type(tcache, key, val);
			
			struct value_pair_list* list = new_value_pair_list();
			
			struct value* new = new_dict_value(type, list);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			free_value_pair_list(list);
		}
		else if (zexpression->emptyset)
		{
			struct type* etype = build_type(tcache, zexpression->emptyset);
			
			struct type* ltype = type_cache_get_list_type(tcache, etype);
			
			struct value_list* set = new_value_list();
			
			struct value* new = new_set_value(ltype, set);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			
			free_value_list(set);
		}
		else if (zexpression->elements.n)
		{
			retval = specialize_primary_set_expression(tcache, scope, zexpression);
		}
		else if (zexpression->keyvalues.n)
		{
			retval = specialize_primary_dict_expression(tcache, scope, zexpression);
		}
		else
		{
			TODO;
		}
	}
	else if (zexpression->paren)
	{
		if (zexpression->elements.n != 1 || zexpression->comma)
		{
			retval = specialize_tuple_expression(tcache, scope, zexpression);
		}
		else
		{
			assert(zexpression->elements.n == 1);
			
			struct expression* sub = specialize_expression(tcache,
				scope, zexpression->elements.data[0]);
			
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
		if (zexpression->emptytype)
		{
			struct type* etype = build_type(tcache, zexpression->emptytype);
			
			struct type* ltype = type_cache_get_list_type(tcache, etype);
			
			struct value_list* list = new_value_list();
			
			struct value* new = new_list_value(ltype, list);
			
			retval = new_literal_expression(new);
			
			free_value(new);
			
			free_value_list(list);
		}
		else
		{
			retval = specialize_primary_list_expression(tcache,
				scope, zexpression);
		}
	}
	else if (zexpression->len_form)
	{
		retval = specialize_primary_len_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->float_form)
	{
		retval = specialize_primary_float_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->int_form)
	{
		retval = specialize_primary_int_form_expression(tcache,
			scope, zexpression->arg);
	}
	else if (zexpression->crossmap_form)
	{
		retval = specialize_primary_crossmap_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	else if (zexpression->map_form)
	{
		retval = specialize_primary_map_form_expression(tcache,
			scope, zexpression->args.data, zexpression->args.n);
	}
	#if 0
	else if (zexpression->sum)
	{
		retval = specialize_primary_sum_expression(tcache,
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

















