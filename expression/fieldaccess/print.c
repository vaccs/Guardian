
#include <debug.h>

#include "../print.h"

#include "struct.h"
#include "print.h"

void fieldaccess_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_fieldaccess);
	
	struct fieldaccess_expression* this = (void*) super;
	
	expression_print(this->object);
	
	printf(".");
	
	printf("%.*s", this->fieldname->len, this->fieldname->chars);
	
	EXIT;
}

