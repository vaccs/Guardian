
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/free.h>

#include <mpz/struct.h>
#include <mpz/new.h>
#include <mpz/free.h>

#include <value/string/struct.h>
#include <value/list/struct.h>
#include <value/dict/struct.h>
#include <value/set/struct.h>

#include <list/value/struct.h>

#include <list/value_pair/struct.h>

#include <value/int/new.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* len_form_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct len_form_expression* this = (void*) super;
	
	struct value* object = expression_evaluate(tcache, this->object, environment);
	
	struct mpz* mpz = new_mpz();
	
	switch (object->kind)
	{
		case vk_string:
			mpz_set_ui(mpz->mpz, ((struct string_value*) object)->len);
			break;
		
		case vk_list:
			mpz_set_ui(mpz->mpz, ((struct list_value*) object)->elements->n);
			break;
		
		case vk_dict:
			mpz_set_ui(mpz->mpz, ((struct dict_value*) object)->elements->n);
			break;
		
		case vk_set:
			mpz_set_ui(mpz->mpz, ((struct set_value*) object)->elements->n);
			break;
		
		default:
			TODO;
			break;
	}
	
	struct value* value = new_int_value(super->type, mpz);
	
	free_value(object);
	
	free_mpz(mpz);
	
	EXIT;
	return value;
}













