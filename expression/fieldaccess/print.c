
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

struct stringtree* fieldaccess_expression_print(
	struct expression* super)
{
	ENTER;
	
	TODO;
	#if 0
	assert(super->kind == ek_fieldaccess);
	
	struct fieldaccess_expression* this = (void*) super;
	
	expression_print(this->object);
	
	printf(".");
	
	printf("%.*s", this->fieldname->len, this->fieldname->chars);
	#endif
	
	EXIT;
}

