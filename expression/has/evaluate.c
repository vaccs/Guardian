
#include <assert.h>

#include <debug.h>

#include <value/struct.h>
#include <value/int/new.h>
/*#include <value/free.h>*/

/*#include <mpz/add.h>*/
/*#include <mpz/subtract.h>*/
/*#include <mpz/multiply.h>*/
/*#include <mpz/free.h>*/

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* has_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	TODO;
	#if 0
	struct has_expression* this = (void*) super;
	
	struct value* list = expression_evaluate(this->list, scope);
	
	assert(list->kind == vk_list);
	
	struct list_value* spef_list = (void*) spef_list;
	
	struct mpz* number;
	
	switch (this->kind)
	{
		case imek_add:
			number = new_mpz_from_add(spef_left->int, spef_right->int);
			break;
		
		case imek_subtract:
			number = new_mpz_from_subtract(spef_left->int, spef_right->int);
			break;
		
		case imek_multiply:
			number = new_mpz_from_multiply(spef_left->int, spef_right->int);
			break;
	}
	
	struct value* value = new_int_value(super->type, number);
	
	free_value(left), free_value(right);
	
	free_mpz(number);
	
	EXIT;
	return value;
	#endif
}













