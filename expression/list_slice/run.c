
#include <assert.h>
#include <debug.h>

#include <gmp.h>

/*#include <list/value/struct.h>*/
/*#include <list/value/new.h>*/
/*#include <list/value/extend.h>*/
/*#include <list/value/free.h>*/

/*#include <value/list/struct.h>*/
/*#include <value/list/new.h>*/

/*#include <mpz/struct.h>*/

/*#include <value/inc.h>*/
/*#include <value/int/struct.h>*/

/*#include <value/list/struct.h>*/

#include "run.h"

struct value* list_slice_run(
	struct type* type,
	struct list_value* list,
	struct int_value* startindex,
	struct int_value*   endindex)
{
/*	struct value* value;*/
	ENTER;
	
	TODO;
	#if 0
	if (mpz_fits_uint_p(index->value->mpz))
	{
		unsigned long raw_index = mpz_get_ui(index->value->mpz);
		
		dpv(raw_index);
		
		if (raw_index < list->elements->n)
		{
			value = inc_value(list->elements->data[raw_index]);
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
	return value;
	#endif
}















