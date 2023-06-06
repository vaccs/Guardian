
#include <string.h>
#include <stdlib.h>

#include <debug.h>

#include <mpz/new.h>
#include <mpz/struct.h>
#include <mpz/free.h>

#include <value/bool/struct.h>

#include <value/float/struct.h>

#include <value/string/struct.h>

#include <value/int/new.h>

#include "run.h"

struct value* int_form_run_on_bool(
	struct type* type,
	struct bool_value* value)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_set_ui(mpz->mpz, value->value);
	
	struct value* result = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return result;
}

struct value* int_form_run_on_float(
	struct type* type,
	struct float_value* value)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	mpz_set_d(mpz->mpz, value->value);
	
	struct value* result = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return result;
}

struct value* int_form_run_on_string(
	struct type* type,
	struct string_value* value)
{
	ENTER;
	
	char* buffer = malloc(value->len + 1);
	
	memcpy(buffer, value->chars, value->len);
	
	buffer[value->len] = 0;
	
	dpvs(buffer);
	
	struct mpz* mpz = new_mpz_from_string(buffer);
	
	struct value* result = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	free(buffer);
	
	EXIT;
	return result;
}

