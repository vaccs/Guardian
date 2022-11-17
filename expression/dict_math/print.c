
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* dict_math_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_dict_math);
	
	struct dict_math_expression* this = (void*) super;
	
	switch (this->kind)
	{
		case dmek_union:
			expression_print(this->left), printf(" | "), expression_print(this->right);
			break;
		
		case dmek_intersect:
			expression_print(this->left), printf(" & "), expression_print(this->right);
			break;
		
		case dmek_difference:
			expression_print(this->left), printf(" - "), expression_print(this->right);
			break;
		
		case dmek_symdifference:
			expression_print(this->left), printf(" ^ "), expression_print(this->right);
			break;
	}
	#endif
	
	EXIT;
}

