
#include <assert.h>

#include <debug.h>

#include <list/value/foreach.h>

#include <value/list/struct.h>

#include <value/int/struct.h>
#include <value/int/new.h>

#include <value/float/struct.h>
#include <value/float/new.h>

#include <mpz/struct.h>
#include <mpz/new.h>
#include <mpz/free.h>

#include "run.h"

struct value* sum_form_run_on_ints(
	struct type* type,
	struct list_value* list)
{
	ENTER;
	
	struct mpz* mpz = new_mpz();
	
	value_list_foreach(list->elements, ({
		void runme(struct value* element)
		{
			assert(element->kind == vk_int);
			
			struct int_value* i = (void*) element;
			
			mpz_add(mpz->mpz, mpz->mpz, i->value->mpz);
		}
		runme;
	}));
	
	struct value* value = new_int_value(type, mpz);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}

struct value* sum_form_run_on_floats(
	struct type* type,
	struct list_value* list)
{
	ENTER;
	
	long double val = 0;
	
	value_list_foreach(list->elements, ({
		void runme(struct value* element)
		{
			assert(element->kind == vk_float);
			
			struct float_value* i = (void*) element;
			
			val += i->value;
		}
		runme;
	}));
	
	struct value* value = new_float_value(type, val);
	
	EXIT;
	return value;
}




















