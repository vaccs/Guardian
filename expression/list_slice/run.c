
#include <stdlib.h>

#include <assert.h>
#include <debug.h>

#include <gmp.h>

#include <mpz/struct.h>

#include <list/value/struct.h>
#include <list/value/new.h>
#include <list/value/append.h>
#include <list/value/free.h>

#include <value/list/struct.h>
#include <value/list/new.h>

#include <value/int/struct.h>

#include "run.h"

struct value* list_slice_run(
	struct type* type,
	struct list_value* list,
	struct int_value* startindex,
	struct int_value*   endindex)
{
	ENTER;
	
	unsigned native_start;
	if (startindex)
	{
		if (mpz_fits_uint_p(startindex->value->mpz))
		{
			native_start = mpz_get_ui(startindex->value->mpz);
			
			if (native_start > list->elements->n)
			{
				TODO;
				exit(1);
			}
		}
		else
		{
			TODO;
		}
	}
	else
	{
		native_start = 0;
	}
	
	unsigned native_end;
	if (endindex)
	{
		if (mpz_fits_uint_p(endindex->value->mpz))
		{
			native_end = mpz_get_ui(endindex->value->mpz);
			
			if (native_end > list->elements->n)
			{
				TODO;
				exit(1);
			}
		}
		else
		{
			TODO;
		}
	}
	else
	{
		native_end = list->elements->n;
	}
	
	dpv(native_start);
	
	dpv(native_end);
	
	struct value_list* elements = new_value_list();
	
	for (unsigned index = native_start; index < native_end; index++)
	{
		value_list_append(elements, list->elements->data[index]);
	}
	
	struct value* value = new_list_value(type, elements);
	
	free_value_list(elements);
	
	EXIT;
	return value;
}















