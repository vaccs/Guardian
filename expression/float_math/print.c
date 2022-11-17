
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* float_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	struct float_math_expression* this = (void*) super;
	switch (this->kind)
	{
		case fmek_negate:
			printf("-"), expression_print(this->left);
			break;
		
		case fmek_add:
			expression_print(this->left), printf(" + "), expression_print(this->right);
			break;
		
		case fmek_subtract:
			expression_print(this->left), printf(" - "), expression_print(this->right);
			break;
		
		case fmek_multiply:
			expression_print(this->left), printf(" * "), expression_print(this->right);
			break;
		
		case fmek_qdivide:
			expression_print(this->left), printf(" / "), expression_print(this->right);
			break;
			
		case fmek_rdivide:
			expression_print(this->left), printf(" %% "), expression_print(this->right);
			break;
		
		case fmek_expo:
			expression_print(this->left), printf(" ** "), expression_print(this->right);
			break;
	}
	#endif
	
	EXIT;
}

























