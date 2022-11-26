
#include <assert.h>

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include <value/int/struct.h>

#include <value/string/struct.h>

#include <value/float/new.h>

#include <mpz/struct.h>

#include "run.h"

struct value* float_form_run_on_int(
	struct type* type,
	struct int_value* value)
{
	ENTER;
	
	long double val = mpz_get_d(value->value->mpz);
	
	dpv(val);
	
	struct value* result = new_float_value(type, val);
	
	EXIT;
	return result;
}


struct value* float_form_run_on_string(
	struct type* type,
	struct string_value* value)
{
	ENTER;
	
	char* buffer = malloc(value->len + 1);
	
	mempcpy(buffer, value->chars, value->len);
	
	buffer[value->len] = 0;
	
	dpvs(buffer);
	
	errno = 0;
	
	char* m;
	long double val = strtold(buffer, &m);
	
	if (errno || *m)
	{
		TODO;
		exit(1);
	}
	
	struct value* result = new_float_value(type, val);
	
	free(buffer);
	
	EXIT;
	return result;
}

















