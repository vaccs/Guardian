
#include <assert.h>

#include <debug.h>

#include <value/int/struct.h>
#include <value/int/new.h>
#include <value/free.h>

/*#include <mpz/add.h>*/
/*#include <mpz/subtract.h>*/
/*#include <mpz/multiply.h>*/
/*#include <mpz/free.h>*/

#include "../evaluate.h"

#include "run.h"
#include "struct.h"
#include "evaluate.h"

struct value* int_math_expression_evaluate(
	struct type_cache* tcache,
	struct expression* super,
	struct value* environment)
{
	ENTER;
	
	struct int_math_expression* this = (void*) super;
	
	struct value* value;
	
	switch (this->kind)
	{
		case imek_negate:
		{
			TODO;
			break;
		}
		
		case imek_add:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_add_run(super->type, (void*) left, (void*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_subtract:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_sub_run(super->type, (void*) left, (void*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_multiply:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_mult_run(super->type, (void*) left, (void*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		default:
		{
			TODO;
			break;
		}
	}
	
	EXIT;
	return value;
}













