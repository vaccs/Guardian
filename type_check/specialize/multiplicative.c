
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <quadmath.h>

#include <assert.h>

#include <debug.h>

#include <parse/parse.h>

#include <type/struct.h>

#include <value/float/struct.h>
#include <value/float/new.h>
#include <value/free.h>

#include <expression/struct.h>
#include <expression/literal/struct.h>
#include <expression/literal/new.h>
#include <expression/float_math/new.h>
#include <expression/int_math/new.h>
#include <expression/int_math/run.h>
#include <expression/free.h>

#include "exponentiation.h"
#include "multiplicative.h"

struct expression* specialize_multiplicative_expression(
	struct type_cache* tcache,
	struct type_check_scope* scope,
	struct zebu_multiplicative_expression* zexpression)
{
	struct expression* retval;
	ENTER;
	
	if (zexpression->base)
	{
		retval = specialize_exponentiation_expression(tcache, scope, zexpression->base);
	}
	else if (zexpression->left)
	{
		assert(zexpression->right);
		
		struct expression* left = specialize_multiplicative_expression(tcache, scope, zexpression->left);
		
		struct expression* right = specialize_exponentiation_expression(tcache, scope, zexpression->right);
		
		if (left->type != right->type)
		{
			TODO;
			exit(1);
		}
		
		bool all_literals = (left->kind == ek_literal && right->kind == ek_literal);
		
		switch (left->type->kind)
		{
			case tk_int:
			{
				if (zexpression->rdiv)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct int_value*  leftint = (void*)  leftlit->value;
						struct int_value* rightint = (void*) rightlit->value;
						
						struct value* value = int_math_rdiv_run(left->type, leftint, rightint);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_int_math_expression(left->type, imek_rdivide, left, right);
					}
				}
				else if (zexpression->qdiv)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct int_value*  leftint = (void*)  leftlit->value;
						struct int_value* rightint = (void*) rightlit->value;
						
						struct value* value = int_math_qdiv_run(left->type, leftint, rightint);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_int_math_expression(left->type, imek_qdivide, left, right);
					}
				}
				else if (zexpression->mult)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct int_value*  leftint = (void*)  leftlit->value;
						struct int_value* rightint = (void*) rightlit->value;
						
						struct value* value = int_math_mult_run(left->type, leftint, rightint);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_int_math_expression(left->type, imek_multiply, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			case tk_float:
			{
				if (zexpression->rdiv)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct float_value*  leftfloat = (void*)  leftlit->value;
						struct float_value* rightfloat = (void*) rightlit->value;
						
						struct value* value = new_float_value(left->type, fmodq(leftfloat->value, rightfloat->value));
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_float_math_expression(left->type, fmek_rdivide, left, right);
					}
				}
				else if (zexpression->qdiv)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct float_value*  leftfloat = (void*)  leftlit->value;
						struct float_value* rightfloat = (void*) rightlit->value;
						
						struct value* value = new_float_value(left->type, leftfloat->value / rightfloat->value);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_float_math_expression(left->type, fmek_qdivide, left, right);
					}
				}
				else if (zexpression->mult)
				{
					if (all_literals)
					{
						struct literal_expression*  leftlit = (void*)  left;
						struct literal_expression* rightlit = (void*) right;
						
						struct float_value*  leftfloat = (void*)  leftlit->value;
						struct float_value* rightfloat = (void*) rightlit->value;
						
						struct value* value = new_float_value(left->type, leftfloat->value * rightfloat->value);
						
						retval = new_literal_expression(value);
						
						free_value(value);
					}
					else
					{
						retval = new_float_math_expression(left->type, fmek_multiply, left, right);
					}
				}
				else
				{
					TODO;
				}
				break;
			}
			
			default:
				TODO;
				break;
		}
		
		free_expression(left), free_expression(right);
	}
	else
	{
		TODO;
	}
	
	EXIT;
	return retval;
}















