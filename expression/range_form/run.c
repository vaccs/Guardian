
#include <assert.h>

#include <debug.h>

#include <value/int/struct.h>

#include <list/value/new.h>

#include <value/list/new.h>

#include <list/value/free.h>
#include <list/value/append.h>

#include <mpz/struct.h>
#include <mpz/new.h>

#include <value/int/new.h>

#include <value/free.h>

#include <mpz/free.h>

#include "run.h"

struct value* range_form_run(
	struct type* ltype,
	struct type* etype,
	struct int_value* start,
	struct int_value* end)
{
	ENTER;
	
	assert(end);
	
	unsigned native_start = 0;
	
	if (start)
	{
		if (mpz_fits_uint_p(start->value->mpz))
		{
			native_start = mpz_get_ui(start->value->mpz);
		}
		else
		{
			TODO;
		}
	}
	
	unsigned native_end;
	if (mpz_fits_uint_p(end->value->mpz))
	{
		native_end = mpz_get_ui(end->value->mpz);
	}
	else
	{
		TODO;
	}
	
	struct value_list* elements = new_value_list();
	
	for (unsigned moving = native_start; moving < native_end; moving++)
	{
		dpv(moving);
		
		struct mpz* mpz = new_mpz_from_unsigned(moving);
		
		struct value* element = new_int_value(etype, mpz);
		
		value_list_append(elements, element);
		
		free_value(element);
		
		free_mpz(mpz);
	}
	
	struct value* result = new_list_value(ltype, elements);
	
	free_value_list(elements);
	
	EXIT;
	return result;
}















