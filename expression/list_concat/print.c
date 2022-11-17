
#include <stdio.h>
#include <assert.h>

#include <debug.h>

/*#include <string/struct.h>*/

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* list_concat_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_list_concat);
	
	struct list_concat_expression* this = (void*) super;
	
	expression_print(this->left);
	
	printf(" + ");
	
	expression_print(this->right);
	#endif
	
	EXIT;
}

