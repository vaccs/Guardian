
#include <assert.h>

#include <debug.h>

/*#include <value/int/struct.h>*/
/*#include <value/int/new.h>*/
/*#include <value/free.h>*/

/*#include <mpz/add.h>*/
/*#include <mpz/subtract.h>*/
/*#include <mpz/multiply.h>*/
/*#include <mpz/free.h>*/

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

struct value* float_math_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	TODO;
	#if 0
	struct float_math_expression* this = (void*) super;
	
	struct value* left = expression_evaluate(this->left, scope);
	struct value* right = expression_evaluate(this->right, scope);
	
	assert(left->kind == vk_int);
	assert(right->kind == vk_int);
	
	struct int_value* spef_left = (void*) left;
	struct int_value* spef_right = (void*) right;
	
	struct mpz* number;
	
	switch (this->kind)
	{
		case imek_add:
			number = new_mpz_from_add(spef_left->integer, spef_right->integer);
			break;
		
		case imek_subtract:
			number = new_mpz_from_subtract(spef_left->integer, spef_right->integer);
			break;
		
		case imek_multiply:
			number = new_mpz_from_multiply(spef_left->integer, spef_right->integer);
			break;
	}
	
	struct value* value = new_int_value(super->type, number);
	
	free_value(left), free_value(right);
	
	free_mpz(number);
	
	EXIT;
	return value;
	#endif
}













