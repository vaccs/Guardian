
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

void set_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_set_math);
	
	struct set_math_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case smek_union:
			expression_print(this->left), printf(" | "), expression_print(this->right);
			break;
		
		case smek_intersect:
			expression_print(this->left), printf(" & "), expression_print(this->right);
			break;
		
		case smek_difference:
			expression_print(this->left), printf(" - "), expression_print(this->right);
			break;
		
		case smek_symdifference:
			expression_print(this->left), printf(" ^ "), expression_print(this->right);
			break;
	}
	
	
	EXIT;
}

