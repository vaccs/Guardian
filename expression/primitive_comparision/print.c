
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

static const char* lookup[] = {
	[cek_equal_to] = "==",
};

void primitive_comparision_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_primitive_comparision);
	
	struct primitive_comparision_expression* this = (void*) super;
	
	expression_print(this->left);
	
	printf(" %s ", lookup[this->kind]);
	
	expression_print(this->right);
	
	EXIT;
}


