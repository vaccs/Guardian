
#include <debug.h>

#include "struct.h"
#include "print.h"

void grammar_type_print(
	struct type* super)
{
	ENTER;
	
	assert(super->kind == tk_grammar);
	
	struct grammar_type* this = (void*) super;
	
	printf("%.*s", this->name->len, this->name->chars);
	
	EXIT;
}

