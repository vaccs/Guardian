
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <gmp.h>

#include <list/value/struct.h>
/*#include <list/value/new.h>*/
/*#include <list/value/extend.h>*/
/*#include <list/value/free.h>*/

#include <value/string/struct.h>
#include <value/string/new.h>

#include <mpz/struct.h>

#include <value/inc.h>
#include <value/int/struct.h>

#include "run.h"

struct value* string_index_run(
	struct type* type,
	struct string_value* string,
	struct int_value* index)
{
	struct value* value;
	ENTER;
	
	if (mpz_fits_uint_p(index->value->mpz))
	{
		unsigned long raw_index = mpz_get_ui(index->value->mpz);
		
		dpv(raw_index);
		
		if (raw_index < string->len)
		{
			unsigned char code = string->chars[raw_index];
			
			unsigned char* buffer = malloc(1);
			
			*buffer = code;
			
			value = new_string_value(type, buffer, 1);
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
}















