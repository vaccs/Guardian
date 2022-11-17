
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include "struct.h"
#include "print.h"

struct stringtree* variable_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_variable);
	
	struct variable_expression* this = (void*) super;
	
	struct string* name = this->name;
	
	printf("%.*s", name->len, name->chars);
	#endif
	
	EXIT;
}

