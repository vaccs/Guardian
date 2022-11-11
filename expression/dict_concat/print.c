
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

void dict_concat_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_dict_concat);
	
	struct dict_concat_expression* this = (void*) super;
	
	expression_print(this->left);
	
	printf(" + ");
	
	expression_print(this->right);
	
	EXIT;
}

