
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
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			assert(left->kind == vk_int);
			
			value = int_math_negate_run(super->type, (struct int_value*) left);
			
			free_value(left);
			break;
		}
		
		case imek_bitnot:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			assert(left->kind == vk_int);
			
			value = int_math_bitnegate_run(super->type, (struct int_value*) left);
			
			free_value(left);
			break;
		}
		
		case imek_add:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_add_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_subtract:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_sub_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_multiply:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_mult_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_rdivide:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_rdiv_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_qdivide:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_qdiv_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_expo:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_expo_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_bitand:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_bitand_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_bitior:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_bitior_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_bitxor:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_bitxor_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_lshift:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_lshift_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
			free_value(left), free_value(right);
			break;
		}
		
		case imek_rshift:
		{
			struct value* left = expression_evaluate(tcache, this->left, environment);
			
			struct value* right = expression_evaluate(tcache, this->right, environment);
			
			assert(left->kind == vk_int && right->kind == vk_int);
			
			value = int_math_rshift_run(super->type, (struct int_value*) left, (struct int_value*) right);
			
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













