
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void int_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	struct int_math_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case imek_negate:
			printf("-"), expression_print(this->left);
			break;
		
		case imek_add:
			expression_print(this->left), printf(" + "), expression_print(this->right);
			break;
		
		case imek_subtract:
			expression_print(this->left), printf(" - "), expression_print(this->right);
			break;
		
		case imek_multiply:
			expression_print(this->left), printf(" * "), expression_print(this->right);
			break;
		
		case imek_qdivide:
			expression_print(this->left), printf(" / "), expression_print(this->right);
			break;
			
		case imek_rdivide:
			expression_print(this->left), printf(" %% "), expression_print(this->right);
			break;
		
		case imek_expo:
			expression_print(this->left), printf(" ** "), expression_print(this->right);
			break;
		
		case imek_bitnot:
			printf("~"), expression_print(this->left);
			break;
		
		case imek_bitand:
			expression_print(this->left), printf(" & "), expression_print(this->right);
			break;
		
		case imek_bitxor:
			expression_print(this->left), printf(" ^ "), expression_print(this->right);
			break;
		
		case imek_bitior:
			expression_print(this->left), printf(" | "), expression_print(this->right);
			break;
		
		case imek_lshift:
			expression_print(this->left), printf(" << "), expression_print(this->right);
			break;
		
		case imek_rshift:
			expression_print(this->left), printf(" >> "), expression_print(this->right);
			break;
	}
	
	EXIT;
}

























