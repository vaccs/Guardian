
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
	struct expression* super,
	struct scope* scope)
{
	ENTER;
	
	struct int_math_expression* this = (void*) super;
	
	struct value* value;
	
	switch (this->kind)
	{
		case imek_add:
		{
			struct value* left = expression_evaluate(this->left, scope);
			struct value* right = expression_evaluate(this->right, scope);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_add_run(super->type, (void*) left, (void*) right);
			
			free_value(left), free_value(right);
			
			break;
		}
		
		case imek_subtract:
		{
			TODO;
			break;
		}
		
		case imek_multiply:
		{
			TODO;
			break;
		}
		
		case imek_negate:
		{
			TODO;
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













