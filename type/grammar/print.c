
#include <stdio.h>
#include <assert.h>

#include <debug.h>

#include <string/struct.h>

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

