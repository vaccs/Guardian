
#include <debug.h>

#include <parse/parse.h>

#include <mpz/new.h>

#include <value/int/new.h>

#include <type_cache/get_int_type.h>

#include <expression/literal/new.h>

#include <value/free.h>

#include <mpz/free.h>

#include "integer.h"

struct expression* specialize_primary_integer_expression(
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

