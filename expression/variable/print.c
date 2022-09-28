
#include <debug.h>

#include "struct.h"
#include "print.h"

void variable_expression_print(
	struct expression* super)
{
	ENTER;
	
	assert(super->kind == ek_variable);
	
	struct variable_expression* this = (void*) super;
	
	struct string* name = this->name;
	
	printf("%.*s", name->len, name->chars);
	
	EXIT;
}
