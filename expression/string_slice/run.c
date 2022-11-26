
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <gmp.h>

/*#include <list/value/struct.h>*/
/*#include <list/value/new.h>*/
/*#include <list/value/extend.h>*/
/*#include <list/value/free.h>*/

#include <value/string/struct.h>
#include <value/string/new.h>

#include <mpz/struct.h>

/*#include <value/inc.h>*/
#include <value/int/struct.h>

/*#include <value/list/struct.h>*/

#include "run.h"

struct value* string_slice_run(
	struct type* type,
	struct string_value* string,
	struct int_value* startindex,
	struct int_value*   endindex)
{
	ENTER;
	
	unsigned native_startindex = 0;
	
	unsigned native_endindex = string->len;
	
	if (startindex)
	{
		if (mpz_fits_uint_p(startindex->value->mpz))
		{
			native_startindex = mpz_get_ui(startindex->value->mpz);
			
			if (native_startindex > string->len)
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
	
	if (endindex)
	{
		if (mpz_fits_uint_p(endindex->value->mpz))
		{
			native_endindex = mpz_get_ui(endindex->value->mpz);
			
			if (native_endindex > string->len)
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
	
	if (native_endindex < native_startindex)
	{
		native_startindex = native_endindex = 0;
	}
	
	dpv(native_startindex);
	dpv(native_endindex);
	
	unsigned len = native_endindex - native_startindex;
	
	unsigned char* buffer = malloc(len);
	
	memcpy(buffer, string->chars + native_startindex, len);
	
	struct value* value = new_string_value(type, buffer, len);
	
	EXIT;
	return value;
}















